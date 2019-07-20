#include <bits/stdc++.h>

using namespace std;

unsigned long long chocho(int n, int k) {
    if (n < k) {
        return 0;
    }
    if (n == k || k == 0) {
        return 1;
    }
    return chocho(n - 1, k - 1) + chocho(n - 1, k);
}

int main() {
    freopen("choose2num.in", "r+", stdin);
    freopen("choose2num.out", "w+", stdout);
    int n, k;
    cin >> n >> k;

    vector<int> mas(k);
    for (int i = 0; i < k; i++) {
        cin >> mas[i];
    }

    unsigned long long ans = 0;
    for (int i = 0; i < k; i++) {
        for (int j = (i == 0) ? 1 : mas[i - 1] + 1; j < mas[i]; j++) {
            ans += chocho(n - j, k - i - 1);
        }
    }

    cout << ans;
    return 0;
}