#include <iostream>
#include <vector>

using namespace std;

vector<int> u, c, used;
vector<vector<int>> g, rev;
int answer = -1;


int dfs2(int x) {
    c[x] = 0;
    int y = used[x];

    for (int next : g[x]) {
        if (c[next] == 2) {
            y += dfs2(next);
        }
    }

    answer += (y == 0);
    return y;
}

int gett(int x) {
    while (u[x] != x) {
        u[x] = u[u[x]];
    }
    return u[x];
}

void uni(int x, int i) {
    u[gett(i)] = gett(x);
}

void dfs(int v) {
    c[v] = 1;

    for (int next : g[v]) {
        if (c[next] != 0) continue;

        dfs(next);
        uni(v, next);
    }

    for (int next : rev[v]) {
        if (c[next] == 2) {
            int z = gett(next);
            used[z] -= 2;
            used[next]++;
            used[v]++;
        }
    }

    c[v] = 2;
}


int main() {
    int n;
    cin >> n;

    g.resize(n);
    rev.resize(n);
    u.resize(n);
    c.resize(n, 0);
    used.resize(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        g[x].push_back(y);
        g[y].push_back(x);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        b--, e--;

        rev[b].push_back(e);
        rev[e].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        u[i] = i;
    }

    dfs(0);
    dfs2(0);

    cout << answer << endl;
    return 0;
}