#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

void dfs(int v, vector<unordered_set<int>> &tree, vector<vector<int>> &bl, vector<int> &depth, vector<bool> &used) {
    if (used[v]) return;
    used[v] = true;

    for (int i = 1; i < bl[v].size(); i++) {
        if (bl[v][i - 1] == -1) bl[v][i] = -1;
        else bl[v][i] = bl[bl[v][i - 1]][i - 1];
    }

    for (int next : tree[v]) {
        if (used[next]) continue;
        depth[next] = depth[v] + 1;
        dfs(next, tree, bl, depth, used);
    }
}

int main() {
    int n;
    cin >> n;

    vector<unordered_set<int>> tree(n);
    vector<vector<int>> bl(n, vector<int>(32, -1));

    for (int i = 1; i < n; i++) {
        int v;
        cin >> v;

        tree[i].insert(v - 1);
        tree[v - 1].insert(i);
        bl[i][0] = v - 1;
    }

    vector<bool> used(n, false);
    vector<int> depth(n, 0);
    dfs(0, tree, bl, depth, used);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        if (depth[v] < depth[u]) swap(u, v);
        while (depth[u] != depth[v]) {
            v = bl[v][(int) log2(depth[v] - depth[u])];
        }

        if (u == v) {
            cout << u + 1 << endl;
            continue;
        }

        while (bl[u][0] != bl[v][0]) {
            int p = 31;
            while (bl[u][p] == bl[v][p]) {
                p--;
            }

            u = bl[u][p];
            v = bl[v][p];
        }

        cout << bl[u][0] + 1 << endl;
    }
    return 0;
}