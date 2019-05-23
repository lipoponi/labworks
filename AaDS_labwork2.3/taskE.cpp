#include <iostream>
#include <vector>

using namespace std;


vector<int> p, cnt;
vector<bool> used;
vector<char> color;
vector<vector<int>> tree, ways;
int answer = -1;


int get(int x) {
    if (p[x] == x) return x;
    else return p[x] = get(p[x]);
}

void join(int x, int y) {
    p[get(y)] = get(x);
}

void dfsPre(int v) {
    color[v] = 1;

    for (int next : tree[v]) {
        if (color[next] != 0) continue;

        dfsPre(next);
        join(v, next);
    }

    for (int next : ways[v]) {
        if (color[next] == 2) {
            int z = get(next);
            cnt[z] -= 2;
            cnt[next]++;
            cnt[v]++;
        }
    }

    color[v] = 2;
}

int dfsAns(int x) {
    used[x] = true;
    int y = cnt[x];

    for (int next : tree[x]) {
        if (used[next]) continue;
        y += dfsAns(next);
    }

    answer += (y == 0);
    return y;
}


int main() {
    int n;
    cin >> n;

    tree.resize(n);
    ways.resize(n);
    p.resize(n);
    color.resize(n, 0);
    used.resize(n, false);
    cnt.resize(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        b--, e--;

        ways[b].push_back(e);
        ways[e].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    dfsPre(0);
    dfsAns(0);

    cout << answer << endl;
    return 0;
}