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
    freopen("ufo.in", "r+", stdin);
    freopen("ufo.out", "w+", stdout);
#endif

    int n, v;
    cin >> n >> v;

    A.resize(n);
    B.assign(n, -1);

    struct observation {
        int time;
        int x, y;

        bool operator<(const observation &other) {
            return time < other.time;
        }
    };

    vector<observation> obs(n);
    for (int i = 0; i < n; frees.insert(i), i++) {
        char colon;
        int h, m;

        cin >> h >> colon >> m >> obs[i].x >> obs[i].y;
        obs[i].time = h * 60 + m;
    }

    sort(obs.begin(), obs.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ul xd = abs(obs[i].x - obs[j].x);
            ul yd = abs(obs[i].y - obs[j].y);
            ul d = xd * xd + yd * yd;

            ul t = obs[j].time - obs[i].time;
            ul left = 3600 * d;
            ul right = t * t * v * v;

            if (left <= right) {
                A[i].push_back(j);
            }
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

    int answer = 0;
    for (int p : B) {
        answer += p == -1;
    }

    cout << answer << endl;
    return 0;
}
