#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

vector<pair<int, int>> edges;
vector<vector<int>> graph;
vector<bool> used;
vector<bool> cutpoint;
set<int> cutpoints;
vector<int> tin, up;
vector<int> colors;
int tick = 0, maxColor = 0;

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

void paint(int v, int color, int p = -1) {
    used[v] = true;
    for (int e : graph[v]) {
        auto[a, b] = edges[e];
        if (b == v) {
            swap(a, b);
        }

        if (b == p) {
            continue;
        }
        if (!used[b]) {
            if (tin[v] <= up[b]) {
                int newColor = ++maxColor;
                colors[e] = newColor;
                paint(b, newColor, v);
            } else {
                colors[e] = color;
                paint(b, color, v);
            }
        } else if (tin[b] < tin[v]) {
            colors[e] = color;
        }
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
    colors.resize(m, -1);

    set<pair<int, int>> ue;

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        b--;
        e--;

        edges[i] = {b, e};
        if (ue.find({b, e}) == ue.end()) {
            graph[b].push_back(i);
            graph[e].push_back(i);
        }

        ue.insert({b, e});
        ue.insert({e, b});
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }

    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            maxColor++;
            paint(i, maxColor);
        }
    }

    map<pair<int, int>, int> clmp;
    for (int i = 0; i < m; i++) {
        if (colors[i] != -1) {
            clmp[edges[i]] = colors[i];
            clmp[{edges[i].second, edges[i].first}] = colors[i];
        }
    }

    for (int i = 0; i < m; i++) {
        colors[i] = clmp[edges[i]];
    }

    map<int, int> nc;
    for (int c : colors) {
        if (nc.find(c) == nc.end()) {
            nc[c] = nc.size();
        }
    }

    cout << nc.size() << endl;

    for (int c : colors) {
        cout << nc[c] + 1 << " ";
    }

    return 0;
}