#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <iomanip>

using namespace std;

void dfs(int v, vector<unordered_set<int>> &tree, vector<vector<int>> &bl, vector<vector<int>> &minBl, vector<int> &depth, vector<bool> &used) {
    if (used[v]) return;
    used[v] = true;

    for (int i = 1; i < bl[v].size(); i++) {
        if (bl[v][i - 1] == -1) {
            bl[v][i] = -1;
            minBl[v][i] = INT32_MAX;
        } else {
            bl[v][i] = bl[bl[v][i - 1]][i - 1];
            minBl[v][i] = min(minBl[v][i - 1], minBl[bl[v][i - 1]][i - 1]);
        }
    }

    for (int next : tree[v]) {
        if (used[next]) continue;
        depth[next] = depth[v] + 1;
        dfs(next, tree, bl, minBl, depth, used);
    }
}

int main() {
#ifndef DEBUG
    freopen("minonpath.in", "r+", stdin);
    freopen("minonpath.out", "w+", stdout);
    ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
#endif

    int n;
    cin >> n;

    vector<unordered_set<int>> tree(n);
    vector<vector<int>> bl(n, vector<int>(32, -1));
    vector<vector<int>> minBl(n, vector<int>(32, INT32_MAX));

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;

        tree[i].insert(x - 1);
        tree[x - 1].insert(i);
        bl[i][0] = x - 1;
        minBl[i][0] = y;
    }

    vector<bool> used(n, false);
    vector<int> depth(n, 0);
    dfs(0, tree, bl, minBl, depth, used);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        int result = INT32_MAX;

        if (depth[v] < depth[u]) swap(u, v);
        while (depth[u] != depth[v]) {
            result = min(result, minBl[v][(int) log2(depth[v] - depth[u])]);
            v = bl[v][(int) log2(depth[v] - depth[u])];
        }

        if (u == v) {
            cout << result << endl;
            continue;
        }

        while (bl[u][0] != bl[v][0]) {
            int p = 31;
            while (bl[u][p] == bl[v][p]) {
                p--;
            }

            result = min(result, minBl[u][p]);
            u = bl[u][p];
            result = min(result, minBl[v][p]);
            v = bl[v][p];
        }

        result = min(result, min(minBl[u][0], minBl[v][0]));
        cout << result << endl;
    }
    return 0;
}