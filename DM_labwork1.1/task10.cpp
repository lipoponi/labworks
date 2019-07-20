#include <bits/stdc++.h>

using namespace std;

void doGen(vector<int> prefix, int need) {
    if (need <= 0) {
        if (need == 0) {
            cout << prefix[0];
            for (int i = 1; i < prefix.size(); i++) {
                cout << "+" << prefix[i];
            }
            cout << endl;
        }

        return;
    }

    for (int i = prefix.back(); i <= need; i++) {
        vector<int> ne(prefix);
        ne.push_back(i);
        doGen(ne, need - i);
    }
}

int main() {
    freopen("partition.in", "r+", stdin);
    freopen("partition.out", "w+", stdout);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        vector<int> e(1, i);
        doGen(e, n - i);
    }
    return 0;
}