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

    int n, m;
    cin >> n >> m;

    A.resize(n);
    B.assign(m, -1);

    for (int i = 0, tmp; i < n; frees.insert(i), i++) {
        while (cin >> tmp && tmp) {
            A[i].push_back(tmp - 1);
        }
    }

    while (!frees.empty()) {
        bool found = false;
        vector<char> mark(n, '\0');

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

    vector<pair<int, int>> answer;
    for (int i = 0; i < m; i++) {
        if (B[i] != -1) {
            answer.emplace_back(B[i] + 1, i + 1);
        }
    }

    cout << answer.size() << endl;
    for (auto[u, v] : answer) {
        cout << u << " " << v << endl;
    }
    return 0;
}
