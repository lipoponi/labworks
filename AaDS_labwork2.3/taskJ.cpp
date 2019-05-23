#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> sz;
vector<unordered_set<int>> tree;
vector<int> decomposition;

int findCentroid(int v) {
    int heavy = -1;
    for (int kid : tree[v]) {
        if (sz[v] < sz[kid] * 2 && (heavy == -1 || sz[heavy] < sz[kid])) {
            heavy = kid;
        }
    }

    if (heavy == -1) {
        for (int kid : tree[v]) {
            tree[kid].erase(v);

            int kidCentroid = findCentroid(kid);
            decomposition[kidCentroid] = v;
        }

        return v;
    } else {
        if (sz[heavy] < sz[v]) {
            sz[v] -= sz[heavy];
            sz[heavy] += sz[v];
        }

        return findCentroid(heavy);
    }
}

void dfs(int v) {
    sz[v] = 1;
    for (int next : tree[v]) {
        if (sz[next] != 0) continue;
        dfs(next);
        sz[v] += sz[next];
    }
}

int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#endif

    int n;
    scanf("%d", &n);

    tree.resize(n);
    sz.resize(n, 0);
    decomposition.resize(n, -1);

    for (int i = 1; i < n; i++) {
        int v, u;
        scanf("%d %d", &v, &u);
        v--, u--;

        tree[v].insert(u);
        tree[u].insert(v);
    }

    dfs(0);
    findCentroid(0);

    for (int e : decomposition) {
        printf("%d ", e + 1);
    }
    return 0;
}