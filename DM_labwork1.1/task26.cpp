#include <bits/stdc++.h>

using namespace std;

int n, k;

vector<vector<int>> nextPartits(vector<vector<int>> src) {
    set<int> buff;
    bool outie = false;

    for (int i = src.size() - 1; 0 <= i; i--) {
        if (!buff.empty() && (*buff.rbegin()) > src[i].back()) {
            auto it = buff.upper_bound(src[i].back());
            int e = *it;
            buff.erase(it);
            src[i].push_back(e);
            break;
        }
        for (int j = src[i].size() - 1; 0 <= j; j--) {
            if (!buff.empty() && j && (*buff.rbegin()) > src[i][j]) {
                auto it = buff.upper_bound(src[i][j]);
                int e = *it;
                buff.erase(it);
                buff.insert(src[i][j]);
                src[i][j] = e;
                outie = true;
                break;
            } else {
                buff.insert(src[i][j]);
                src[i].pop_back();
            }
        }
        if (outie) {
            break;
        }
    }

    vector<vector<int>> ans;
    for (vector<int> s : src) {
        if (!s.empty()) {
            ans.push_back(s);
        }
    }

    for (int elem : buff) {
        ans.push_back(vector<int>(1, elem));
    }

    return ans;
}

int main() {
    freopen("nextsetpartition.in", "r+", stdin);
    freopen("nextsetpartition.out", "w+", stdout);
    cin >> n >> k;
    while (n != 0 && k != 0) {
        string e;
        getline(cin, e);
        vector<vector<int>> partit(k);
        for (int i = 0; i < k; i++) {
            string line;
            getline(cin, line);
            const char *ln = line.c_str();
            int tmp;
            char *end = const_cast<char *>(ln);

            while ((tmp = strtol(end, &end, 10)) != 0) {
                partit[i].push_back(tmp);
            }
        }

        vector<vector<int>> ans = nextPartits(partit);

        cout << n << " " << ans.size() << endl;
        for (vector<int> ln : ans) {
            for (int elem : ln) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;

        cin >> n >> k;
    }
    return 0;
}