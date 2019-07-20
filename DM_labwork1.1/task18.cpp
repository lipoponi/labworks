#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
    freopen("brackets2num.in", "r+", stdin);
    freopen("brackets2num.out", "w+", stdout);
    string brackets;
    cin >> brackets;

    vector<vector<ull>> dp(brackets.size() + 2, vector<ull>(brackets.size() + 2, 0));
    dp[0][0] = 1;
    for (int i = 1; i < dp.size() - 1; i++) {
        dp[i][0] = dp[i - 1][1];
        for (int j = 1; j < dp[i].size() - 1; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
        }
    }

    ull ans = 0;
    int balance = 0;
    for (int i = 0; i < brackets.size(); i++) {
        for (char j = '('; j < brackets[i]; j++) {
            ans += dp[brackets.size() - i - 1][balance + 1];
        }

        if (brackets[i] == '(') {
            balance++;
        } else {
            balance--;
        }
    }

    cout << ans;
    return 0;
}