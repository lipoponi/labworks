#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("nextchoose.in", "r+", stdin);
    freopen("nextchoose.out", "w+", stdout);
    int n, k;
    cin >> n >> k;

    vector<int> e(k);
    for (int i = 0; i < k; i++) {
        cin >> e[i];
    }

    e.push_back(n + 1);
    int i = k - 1;
    while (0 <= i && e[i+1] - 2 < e[i]) {
        i--;
    }

    if (0 <= i) {
        e[i]++;
        for (int j = i + 1; j < k; j++) {
            e[j] = e[j - 1] + 1;
        }
        e.pop_back();

        for (int elem : e) {
            cout << elem << " ";
        }
    } else {
        cout << -1 << endl;
    }
    return 0;
}