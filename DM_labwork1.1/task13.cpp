#include <bits/stdc++.h>

using namespace std;

unsigned long long factorial(int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

int main() {
    freopen("num2perm.in", "r+", stdin);
    freopen("num2perm.out", "w+", stdout);
    long long n, k;
    cin >> n >> k;

    vector<int> pre(n);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            if (find(pre.begin(), pre.end(), j) == pre.end()) {
                if (factorial(n - i - 1) <= k) {
                    k -= factorial(n - i - 1);
                } else {
                    pre[i] = j;
                    break;
                }
            }
        }
    }

    for (int elem : pre) {
        cout << elem << " ";
    }
    return 0;
}