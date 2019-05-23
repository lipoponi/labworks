#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdio>

using namespace std;

int timer = 0;
vector<vector<int>> children;
vector<vector<int>> bl;
vector<int> depth;
vector<int> timeIn;

void dfs(int v) {
    for (int i = 1; i < bl[v].size(); i++) {
        if (bl[v][i - 1] == -1) bl[v][i] = -1;
        else bl[v][i] = bl[bl[v][i - 1]][i - 1];
    }

    timeIn[v] = timer++;
    for (int next : children[v]) {
        depth[next] = depth[v] + 1;
        dfs(next);
    }
    timer++;
}

inline int lca(int u, int v) {
    if (depth[v] < depth[u]) swap(u, v);
    while (depth[u] != depth[v]) {
        v = bl[v][(int) log2(depth[v] - depth[u])];
    }

    if (u == v) {
        return u;
    }

    while (bl[u][0] != bl[v][0]) {
        int p = 19;
        while (bl[u][p] == bl[v][p]) {
            p--;
        }

        u = bl[u][p];
        v = bl[v][p];
    }

    return bl[u][0];
}

inline bool comp(int a, int b) {
    return timeIn[a] < timeIn[b];
}

inline int ans(vector<int> &group) {
    sort(group.begin(), group.end(), comp);

    int result = depth[group[0]];
    for (int i = 1; i < group.size(); i++) {
        int l = lca(group[i - 1], group[i]);
        result += depth[group[i]] - depth[l];
    }

    return result;
}


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#endif

    int n;
    scanf("%d", &n);

    children.resize(n);
    bl.resize(n, vector<int>(20, -1));
    depth.resize(n, 1);
    timeIn.resize(n);

    int root = -1;
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        if (p == -1) {
            root = i;
            bl[i][0] = -1;
        } else {
            children[p - 1].push_back(i);
            bl[i][0] = p - 1;
        }
    }

    dfs(root);

    int g;
    scanf("%d", &g);

    for (int i = 0; i < g; i++) {
        int k;
        scanf("%d", &k);

        vector<int> group(k);
        for (int &e : group) scanf("%d", &e), e--;

        int result = ans(group);
        printf("%d\n", result);
    }
    return 0;
}