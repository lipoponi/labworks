#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

vector<pair<int, int>> edges;
vector<vector<int>> graph;
vector<bool> used;
vector<bool> cutpoint;
set<int> cutpoints;
vector<int> tin, up;
int tick = 0;

void dfs(int v, int p = -1) {
    tick++;
    up[v] = tin[v] = tick;
    used[v] = true;
    int count = 0;

    for (auto e : graph[v]) {
        auto[a, b] = edges[e];
        if (v == b) {
            swap(a, b);
        }

        if (b == p) {
            continue;
        }

        if (used[b]) {
            up[v] = min(up[v], tin[b]);
        } else {
            dfs(b, v);
            count++;
            up[v] = min(up[v], up[b]);
            if (p != -1 && tin[v] <= up[b]) {
                cutpoint[v] = true;
                cutpoints.insert(v);
            }
        }
    }

    if (p == -1 && 2 <= count) {
        cutpoint[v] = true;
        cutpoints.insert(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n);
    edges.resize(m);
    used.resize(n);
    cutpoint.resize(n);
    up.resize(n);
    tin.resize(n);

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        b--;
        e--;

        edges[i] = {b, e};
        graph[b].push_back(i);
        graph[e].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }

    cout << cutpoints.size() << endl;

    for (int cp : cutpoints) {
        cout << cp + 1 << " ";
    }

    return 0;
}