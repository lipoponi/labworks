#include <bits/stdc++.h>

using namespace std;

int n, k;

void doGen(vector<int> prefix) {
    if (prefix.size() == k) {
        for (int elem : prefix) {
            cout << elem << " ";
        }

        cout << endl;
        return;
    }

    for (int i = prefix.back() + 1; i <= n; i++) {
        vector<int> ne(prefix);
        ne.push_back(i);
        doGen(ne);
    }
}

int main() {
    freopen("choose.in", "r+", stdin);
    freopen("choose.out", "w+", stdout);
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        vector<int> ne(1, i);
        doGen(ne);
    }

    return 0;
}