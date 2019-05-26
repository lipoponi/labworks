#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> tree, bl;
vector<int> depth, in, out;
vector<long long> st;
int timer = 0;


void dfs(int v, int p = -1) {
    in[v] = timer++;
    bl[v][0] = p;

    for (int i = 1; i < bl[v].size(); i++) {
        if (bl[v][i - 1] == -1) bl[v][i] = -1;
        else bl[v][i] = bl[bl[v][i - 1]][i - 1];
    }

    for (int next : tree[v]) {
        if (next == p) continue;
        depth[next] = depth[v] + 1;
        dfs(next, v);
    }

    out[v] = timer;
}

inline bool inner(int v, int u) {
    if (v == -1) return true;
    return in[v] <= in[u] && out[u] <= out[v];
}

int lca(int v, int u) {
    if (inner(v, u)) return v;

    for (int i = 18; i >= 0; i--) {
        if (!inner(bl[v][i], u)) v = bl[v][i];
    }

    return bl[v][0];
}

void add(int node, int left, int right, int position, long long d) {
    if (left + 1 == right) {
        st[node] += d;
    } else if (left + 1 < right) {
        int mid = (left + right) / 2;

        if (position < mid) {
            add(node * 2 + 1, left, mid, position, d);
        } else {
            add(node * 2 + 2, mid, right, position, d);
        }

        st[node] = st[node * 2 + 1] + st[node * 2 + 2];
    }
}

long long get(int node, int left, int right, int l, int r) {
    if (right <= l || r <= left) return 0;
    else if (l <= left && right <= r) {
        return st[node];
    } else {
        int mid = (left + right) / 2;
        return get(node * 2 + 1, left, mid, l, r) + get(node * 2 + 2, mid, right, l, r);
    }
}


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif

    int n;
    cin >> n;

    int minP2 = 1;
    while (minP2 < n) minP2 *= 2;

    tree.resize(n);
    bl.resize(n, vector<int>(19, -1));
    in.resize(n);
    out.resize(n);
    st.resize(2 * minP2, 0);

    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;

        tree[v].push_back(u);
        tree[u].push_back(v);
    }

    depth.resize(n, 0);
    dfs(0);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        char command;
        cin >> command;

        if (command == '+') {
            int v, u, d;
            cin >> v >> u >> d;
            v--, u--;

            int c = lca(v, u);
            add(0, 0, minP2, in[v], d);
            add(0, 0, minP2, in[u], d);
            add(0, 0, minP2, in[c], -d);
            if (bl[c][0] != -1) {
                add(0, 0, minP2, in[bl[c][0]], -d);
            }
        } else if (command == '?') {
            int v;
            cin >> v;
            v--;

            cout << get(0, 0, minP2, in[v], out[v]) << endl;
        }
    }
    return 0;
}