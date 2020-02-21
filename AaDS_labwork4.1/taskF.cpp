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
    freopen("dominoes.in", "r+", stdin);
    freopen("dominoes.out", "w+", stdout);
#endif

    sl n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<vector<char>> picture(n, vector<char>(m));
    map<pair<int, int>, int> As, Bs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> picture[i][j];
            if (picture[i][j] == '.') {
                continue;
            }

            map<pair<int, int>, int> &Cs = (i + j) % 2 == 0 ? As : Bs;
            Cs[{i, j}] = Cs.size();
        }
    }

    if (2 * b < a) {
        cout << (As.size() + Bs.size()) * b << endl;
        return 0;
    }

    A.resize(As.size());
    B.assign(Bs.size(), -1);

    for (auto[pos, idx] : As) {
        frees.insert(idx);

        auto[i, j] = pos;
        if (0 < i && picture[i - 1][j] == '*') {
            A[idx].push_back(Bs[{i - 1, j}]);
        }
        if (i + 1 < n && picture[i + 1][j] == '*') {
            A[idx].push_back(Bs[{i + 1, j}]);
        }
        if (0 < j && picture[i][j - 1] == '*') {
            A[idx].push_back(Bs[{i, j - 1}]);
        }
        if (j + 1 < m && picture[i][j + 1] == '*') {
            A[idx].push_back(Bs[{i, j + 1}]);
        }
    }

    while (!frees.empty()) {
        bool found = false;
        vector<char> mark(A.size(), '\0');

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

    int pairs = 0;
    for (int v : B) {
        pairs += (v != -1);
    }

    cout << pairs * a + (A.size() - pairs + B.size() - pairs) * b << endl;
    return 0;
}
