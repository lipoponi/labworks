#include <bits/stdc++.h>

#define endl '\n'
#define fast_io do { ios_base::sync_with_stdio(false); cin.tie(nullptr);  } while (false)
#define precision(n) cout << setprecision(n) << fixed

typedef int64_t sl;
typedef uint64_t ul;

using namespace std;

vector<vector<int>> g;
vector<int> p;
vector<int> w;

set<pair<int, int>, __greater> q;


bool aug(int u, int v, vector<char> &mark) {
    if (mark[u]) return false;
    mark[u] = 1;

    for (int next : g[u]) {
        if (next == v || (p[next] != -1 && aug(p[next], v, mark))) {
            p[u] = next;
            p[next] = u;
            return true;
        }
    }

    return false;
}

int main() {
    fast_io;

    int n, m, e;
    cin >> n >> m >> e;

    g.resize(n + m);
    p.assign(n + m, -1);
    w.resize(n + m);

    for (int i = 0; i < n + m; q.insert({w[i], i}), i++) {
        cin >> w[i];
    }

    map<pair<int, int>, int> edges;
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--, b += n;

        g[a].push_back(b);
        g[b].push_back(a);

        edges[{a, b}] = i;
    }

    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        set<pair<int, int>, __greater> vs;
        vector<char> mark(n + m, '\0');
        function<void(int)> dfs = [&](int v) {
            if (mark[v]) return;
            mark[v] = 1;

            for (int next : g[v]) {
                if (p[next] == -1) {
                    vs.insert({w[next], next});
                } else {
                    dfs(p[next]);
                }
            }
        };
        dfs(u);

        if (!vs.empty()) {
            int v = vs.begin()->second;
            q.erase(*vs.begin());

            mark.assign(n + m, '\0');
            aug(u, v, mark);
        }
    }

    sl sum = 0;
    vector<int> answer;

    for (int i = 0; i < n; i++) {
        if (p[i] != -1) {
            answer.push_back(edges[{i, p[i]}] + 1);
            sum += w[i];
            sum += w[p[i]];
        }
    }

    cout << sum << endl;
    cout << answer.size() << endl;
    for (int idx : answer) cout << idx << " ";

    return 0;
}
