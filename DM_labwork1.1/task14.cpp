#include <bits/stdc++.h>

using namespace std;

unsigned long long factorial(int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

int main() {
    freopen("perm2num.in", "r+", stdin);
    freopen("perm2num.out", "w+", stdout);
    int n;
    cin >> n;
    vector<int> mas(n);

    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }

    unsigned long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < mas[i]; j++) {
            if (find(mas.begin(), mas.begin() + i, j) == mas.begin() + i) {
                ans += factorial(n - i - 1);
            }
        }
    }

    cout << ans;
    return 0;
}