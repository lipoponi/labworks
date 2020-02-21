#include <bits/stdc++.h>

#define endl '\n'
#define fast_io do { ios_base::sync_with_stdio(false); cin.tie(nullptr);  } while (false)
#define precision(n) cout << setprecision(n) << fixed

typedef int64_t sl;
typedef uint64_t ul;

using namespace std;

set<int> frees;
vector<vector<int>> A;
vector<int> B;

bool dfs(int v, vector<char> &mark) {
    if (mark[v]) return false;
    mark[v] = 1;

    for (int next : A[v]) {
        if (B[next] == -1 || dfs(B[next], mark)) {
            B[next] = v;
            frees.erase(v);
            return true;
        }
    }

    return false;
}

int main() {
    fast_io;

#ifndef DEBUG
    freopen("taxi.in", "r+", stdin);
    freopen("taxi.out", "w+", stdout);
#endif

    int M;
    cin >> M;

    struct order {
        int time;
        int a, b, c, d;
    };
    vector<order> orders(M);

    for (int i = 0; i < M; frees.insert(i), i++) {
        char colon;
        int h, m, a, b, c, d;
        cin >> h >> colon >> m >> a >> b >> c >> d;

        orders[i] = {h * 60 + m, a, b, c, d};
    }

    A.resize(M);
    B.assign(M, -1);

    for (int i = 0; i < orders.size(); i++) {
        for (int j = 0; j < orders.size(); j++) {
            int diff = orders[j].time - orders[i].time;
            int need = abs(orders[i].a - orders[i].c) + abs(orders[i].b - orders[i].d)
                       + abs(orders[i].c - orders[j].a) + abs(orders[i].d - orders[j].b);

            if (need < diff) {
                A[i].push_back(j);
            }
        }
    }

    while (!frees.empty()) {
        bool found = false;
        vector<char> mark(M, '\0');

        for (int s : frees) {
            if (dfs(s, mark)) {
                found = true;
                break;
            }
        }

        if (!found) {
            break;
        }
    }

    int answer = 0;
    for (int v : B) {
        if (v == -1) {
            answer++;
        }
    }

    cout << answer << endl;
    return 0;
}
