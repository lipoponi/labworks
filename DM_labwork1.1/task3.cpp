#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> comb;

int main() {
    freopen("antigray.in", "r+", stdin);
    freopen("antigray.out", "w+", stdout);
    int n;
    cin >> n;

    comb.resize(n + 1);
    for (int k = 0; k < 3; k++) {
        comb[1].push_back(string("") + static_cast<char>(k + '0'));
    }

    for (int size = 2; size <= n; size++) {
        for (int i = 0; i < comb[size - 1].size(); i++) {
            for (int k = 0; k < 3; k++) {
                comb[size].push_back(static_cast<char>(k + '0') + comb[size - 1][(i + k) % comb[size - 1].size()]);
            }
        }
    }

    for (int i = 0; i < comb[n].size(); i++) {
        cout << comb[n][i] << endl;
    }
    return 0;
}