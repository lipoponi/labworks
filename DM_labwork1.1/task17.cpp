#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
    freopen("num2brackets.in", "r+", stdin);
    freopen("num2brackets.out", "w+", stdout);
    unsigned long long n, k;
    cin >> n >> k;

    vector<vector<ull>> dp(n * 2 + 2, vector<ull>(n * 2 + 2, 0));
    dp[0][0] = 1;
    for (int i = 1; i < dp.size() - 1; i++) {
        dp[i][0] = dp[i - 1][1];
        for (int j = 1; j < dp[i].size() - 1; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
        }
    }

    string pre;
    int opens = 0, closes = 0;
    for (int i = 0; i < n * 2; i++) {
        for (char j = '('; j <= ')'; j++) {
            if ((j == '(' && opens < n) || (j == ')' && closes < opens)) {
                unsigned long long count = dp[2*n - i - 1][opens - closes + (j == '(' ? 1 : -1)];
                if (count <= k) {
                    k -= count;
                } else {
                    pre += j;
                    if (j == '(') {
                        opens++;
                    } else {
                        closes++;
                    }
                    break;
                }
            }
        }
    }

    cout << pre;
    return 0;
}