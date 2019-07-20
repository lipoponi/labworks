#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
    freopen("part2num.in", "r+", stdin);
    freopen("part2num.out", "w+", stdout);
    vector<int> parts(1);
    cin >> parts[0];

    char c;
    int tmp, n = parts[0];
    while (cin >> c) {
        cin >> tmp;
        parts.push_back(tmp);
        n += tmp;
    }

    vector<vector<ull>> dp(n + 1, vector<ull>(n + 1));
    dp[0] = vector<ull>(n + 1, 1);
    for (int i = 1; i < dp.size(); i++) {
        dp[i][i] = 1;
        for (int j = i - 1; 0 < j; j--) {
            dp[i][j] = dp[i][j + 1] + dp[i - j][j];
        }
        dp[i][0] = dp[i][1];
    }

    int sum = 0;
    ull ans = 0;
    for (int i = 0; i < parts.size(); i++) {
        for (int j = 1; j < parts[i]; j++) {
            if ((i == 0 || parts[i - 1] <= j) && (j == n - sum || j + j <= n - sum)) {
                ans += dp[n - sum - j][j];
            }
        }

        sum += parts[i];
    }

    cout << ans;
    return 0;
}