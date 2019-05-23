#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <iomanip>

using namespace std;

vector<unordered_set<int>> tree;
vector<vector<int>> bl;
vector<int> depth;
vector<bool> isDead;
vector<int> parents;

int lca(int u, int v) {
    if (depth[v] < depth[u]) swap(u, v);
    while (depth[u] != depth[v]) {
        v = bl[v][(int) log2(depth[v] - depth[u])];
    }

    if (u == v) {
        return u;
    }

    while (bl[u][0] != bl[v][0]) {
        int p = 31;
        while (bl[u][p] == bl[v][p]) {
            p--;
        }

        u = bl[u][p];
        v = bl[v][p];
    }

    return bl[u][0];
}

void hang(int node, int to) {
    tree[node].insert(to);
    tree[to].insert(node);
    depth[node] = depth[to] + 1;

    bl[node][0] = to;
    parents[node] = to;

    for (int i = 1; i < bl[node].size(); i++) {
        if (bl[node][i - 1] == -1) bl[node][i] = -1;
        else bl[node][i] = bl[bl[node][i - 1]][i - 1];
    }
}

int aliveParent(int v) {
    int old = v;
    while (isDead[v]) {
        v = parents[v];
    }
    if (isDead[old]) parents[old] = v;
    return v;
}

int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
#endif

    int m;
    cin >> m;

    parents.resize(1, 0);
    tree.resize(1);
    depth.resize(1, 0);
    isDead.resize(1, false);
    bl.resize(1, vector<int>(32, -1));

    for (int i = 0; i < m; i++) {
        char cmd;
        cin >> cmd;

        if (cmd == '+') {
            int v;
            cin >> v;

            v--;

            tree.emplace_back();
            bl.emplace_back(32, -1);
            depth.emplace_back();
            isDead.emplace_back(false);
            parents.emplace_back();

            hang(tree.size() - 1, v);
        } else if (cmd == '-') {
            int v;
            cin >> v;

            v--;

            isDead[v] = true;
        } else if (cmd == '?') {
            int u, v;
            cin >> u >> v;

            u--, v--;

            cout << aliveParent(lca(u, v)) + 1 << endl;
        }
    }
    return 0;
}