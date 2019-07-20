#include <bits/stdc++.h>

using namespace std;

int n;

void doGen(vector<int> prefix) {
    if (prefix.size() <= n) {
        cout << endl;
        cout << prefix[0];
        for (int i = 1; i < prefix.size(); i++) {
            cout << " " << prefix[i];
        }
    }

    if (n <= prefix.size()) {
        return;
    }

    for (int i = prefix.back() + 1; i <= n; i++) {
        vector<int> ne(prefix);
        ne.push_back(i);
        doGen(ne);
    }
}

int main() {
    freopen("subsets.in", "r+", stdin);
    freopen("subsets.out", "w+", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        vector<int> ne(1, i);
        doGen(ne);
    }
    return 0;
}