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

void solve() {
    int m, n;
    cin >> m >> n;

    frees.clear();
    A.clear();
    B.clear();
    A.resize(m);
    B.assign(n, -1);

    vector<set<int>> mA(m);
    for (int i = 0, tmp; i < m; frees.insert(i), i++) {
        while (cin >> tmp && tmp) {
            mA[i].insert(tmp - 1);
        }
    }
//
//    if (n == 2 && m == 2) {
//        cout << "4\n"
//                "2 2\n"
//                "1 2\n"
//                "1 2\n\n";
//        return;
//    }
//
//    if (m == 3 && n == 2) {
//        cout << "4\n"
//                "2 2\n"
//                "1 3\n"
//                "1 2\n\n";
//        return;
//    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mA[i].count(j) == 0) {
                A[i].push_back(j);
            }
        }
    }

    while (!frees.empty()) {
        bool found = false;
        vector<char> mark(m, '\0');

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

    vector<bool> markA(m), markB(n);
    function<void(int)> tfs = [&](int v) {
        if (markA[v]) return;
        markA[v] = true;

        for (int next : A[v]) {
            markB[next] = true;
            if (B[next] != -1) {
                tfs(B[next]);
            }
        }
    };

    for (int v : frees) {
        tfs(v);
    }

    int b = 0, g = 0;

    for (bool f : markA) {
        b += f;
    }

    for (bool f : markB) {
        g += !f;
    }

    cout << b + g << endl;
    cout << b << " " << g << endl;

    for (int i = 0; i < m; i++) {
        if (markA[i]) {
            cout << i + 1 << " ";
        }
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        if (!markB[i]) {
            cout << i + 1 << " ";
        }
    }

    cout << endl;

    cout << endl;
}

int main() {
    fast_io;

#ifndef DEBUG
    freopen("birthday.in", "r+", stdin);
    freopen("birthday.out", "w+", stdout);
#endif

    int k;
    cin >> k;

    while (k--) {
        solve();
    }
    return 0;
}
