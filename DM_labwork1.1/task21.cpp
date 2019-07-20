#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
    freopen("num2part.in", "r+", stdin);
    freopen("num2part.out", "w+", stdout);
    long long n, k;
    cin >> n >> k;

    vector<vector<ull>> dp(n + 1, vector<ull>(n + 1));
    dp[0] = vector<ull>(n + 1, 1);
    for (int i = 1; i < dp.size(); i++) {
        dp[i][i] = 1;
        for (int j = i - 1; 0 < j; j--) {
            dp[i][j] = dp[i][j + 1] + dp[i - j][j];
        }
        dp[i][0] = dp[i][1];
    }

    vector<int> pre;
    int sum = 0;
    while (true) {
        for (int j = 1; j <= n; j++) {
            if ((pre.empty() || pre.back() <= j) && (j == (n - sum) || (j + j) <= (n - sum))) {
                ull count = dp[n - sum - j][j];
                if (count <= k) {
                    k -= count;
                } else {
                    pre.push_back(j);
                    sum += j;
                    break;
                }
            }
        }

        if (sum == n) {
            break;
        }
    }

    cout << pre[0];
    for (int i = 1; i < pre.size(); i++) {
        cout << "+" << pre[i];
    }
    return 0;
}
/*
1+1+1+1+1+1+1+1+1+1
1+1+1+1+1+1+1+1+2
1+1+1+1+1+1+1+3
1+1+1+1+1+1+2+2
1+1+1+1+1+1+4
1+1+1+1+1+2+3
1+1+1+1+1+5
1+1+1+1+2+2+2
1+1+1+1+2+4
1+1+1+1+3+3
1+1+1+1+6
 */