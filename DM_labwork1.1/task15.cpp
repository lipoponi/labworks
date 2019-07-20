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
    freopen("num2choose.in", "r+", stdin);
    freopen("num2choose.out", "w+", stdout);
    unsigned long long n, k, m;
    cin >> n >> k >> m;

    vector<int> result(k);

    for (int i = 0; i < k; i++) {
        for (int j = (i == 0) ? 1 : result[i-1] + 1; j <= n; j++) {
            if (i == 0 || result.back() < j) {
                unsigned long long count = chocho(n - j, k - i - 1);

                if (count <= m) {
                    m -= count;
                } else {
                    result[i] = j;
                    break;
                }
            }
        }
    }

    for (int elem : result) {
        cout << elem << " ";
    }
    return 0;
}