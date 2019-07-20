#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
    freopen("brackets2num2.in", "r+", stdin);
    freopen("brackets2num2.out", "w+", stdout);
    string brackets;
    cin >> brackets;

    vector<vector<ull>> dp(brackets.size() + 2, vector<ull>(brackets.size() + 2, 0));
    dp[0][0] = 1;
    for (int i = 1; i < dp.size() - 1; i++) {
        dp[i][0] = dp[i - 1][1] * 2;
        for (int j = 1; j < dp[i].size() - 1; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1] * 2;
        }
    }

    ull ans = 0;
    stack<char> opens;
    char *alpha = new char[4]{'(', ')', '[', ']'};
    for (int i = 0; i < brackets.size(); i++) {
        for (int j = 0; j < 4; j++) {
            if (brackets[i] == alpha[j]) {
                break;
            }

            if ((j % 2 == 1 && opens.empty()) || (j == 1 && opens.top() != '(') || (j == 3 && opens.top() != '[')) {
                continue;
            }

            ans += dp[brackets.size() - i - 1][opens.size() + (j % 2 == 0 ? 1 : -1)];
        }

        if (brackets[i] == '(' || brackets[i] == '[') {
            opens.push(brackets[i]);
        } else {
            opens.pop();
        }
    }

    cout << ans;
    return 0;
}
/*
 ( +0
 [ +40+36
 ]
 )
 (
 )
 [
 ]

 */