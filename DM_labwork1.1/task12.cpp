#include <bits/stdc++.h>

using namespace std;

int n, k;

vector<vector<set<int>>> dodo(int n) {
    if (n == 1) {
        vector<vector<set<int>>> ans(1);
        ans[0].resize(1);
        ans[0][0].insert(1);
        return ans;
    }

    vector<vector<set<int>>> mini = dodo(n - 1);
    vector<vector<set<int>>> ans;

    for (vector<set<int>> current : mini) {
        for (int i = 0; i < current.size(); i++) {
            vector<set<int>> lili(current);
            lili[i].insert(n);
            ans.push_back(lili);
        }
        if (current.size() < k) {
            set<int> lili;
            lili.insert(n);
            current.push_back(lili);
            ans.push_back(current);
        }
    }

    return ans;
}

int main() {
    freopen("part2sets.in", "r+", stdin);
    freopen("part2sets.out", "w+", stdout);
    cin >> n >> k;

    vector<vector<set<int>>> ans = dodo(n);
    for (auto i : ans) {
        if (i.size() != k) continue;
        for (auto j : i) {
            for (auto e : j) {
                cout << e << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}