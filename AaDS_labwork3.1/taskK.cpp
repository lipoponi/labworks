#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct edge {
    int from = 0, to = 0;
    long long w = 0;
};

bool accessible(int n, int root, vector<edge> &edges) {
    vector<bool> used(n, false);
    vector<vector<int>> f(n);

    for (auto e : edges) {
        f[e.from].push_back(e.to);
    }

    int cnt = 0;
    function<void(int)> dfs = [&](int v) {
        if (used[v]) return;
        used[v] = true;
        cnt++;
        for (int next : f[v]) dfs(next);
    };
    dfs(root);

    return cnt == n;
}

vector<int> condensation(int n, vector<edge> &edges, int &componentCount) {
    vector<vector<int>> f(n), r(n);
    for (auto e : edges) {
        f[e.from].push_back(e.to);
        r[e.to].push_back(e.from);
    }

    vector<bool> used(n, false);
    vector<int> order, newComponents(n, -1);
    componentCount = 0;

    function<void(int)> dfs1 = [&](int v) {
        if (used[v]) return;
        used[v] = true;
        for (auto next : f[v]) dfs1(next);
        order.push_back(v);
    };
    function<void(int)> dfs2 = [&](int v) {
        if (used[v]) return;
        used[v] = true;
        newComponents[v] = componentCount;
        for (auto next : r[v]) dfs2(next);
    };

    for (int i = 0; i < n; i++) dfs1(i);
    reverse(order.begin(), order.end());
    used.assign(n, false);
    for (int v : order) {
        if (!used[v]) {
            dfs2(v);
            componentCount++;
        }
    }

    return newComponents;
}

long long findMST(vector<edge> &edges, int n, int root) {
    long long res = 0;
    vector<long long> minEdge(n, INT64_MAX);
    for (auto e : edges) {
        minEdge[e.to] = min(e.w, minEdge[e.to]);
    }
    for (int v = 0; v < n; v++) {
        if (v == root) continue;
        res += minEdge[v];
    }
    vector<edge> zeroEdges;
    for (auto e : edges) {
        if (e.w == minEdge[e.to]) {
            zeroEdges.push_back({e.from, e.to, 0});
        }
    }

    if (accessible(n, root, zeroEdges)) {
        return res;
    }

    int componentCount;
    vector<int> newComponents = condensation(n, zeroEdges, componentCount);
    vector<edge> newEdges;
    for (auto e : edges) {
        if (newComponents[e.to] != newComponents[e.from]) {
            newEdges.push_back({newComponents[e.from], newComponents[e.to], e.w - minEdge[e.to]});
        }
    }

    res += findMST(newEdges, componentCount, newComponents[root]);
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].w;
        edges[i].from--, edges[i].to--;
    }

    if (!accessible(n, 0, edges)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << findMST(edges, n, 0) << endl;
    }
    return 0;
}