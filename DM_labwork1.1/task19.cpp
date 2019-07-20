#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main() {
//    freopen("num2brackets2.in", "r+", stdin);
//    freopen("num2brackets2.out", "w+", stdout);
    ull n, k;
    cin >> n >> k;

    vector<vector<ull>> dp(n * 2 + 2, vector<ull>(n * 2 + 2, 0));
    dp[0][0] = 1;
    for (int i = 1; i < dp.size() - 1; i++) {
        dp[i][0] = dp[i - 1][1] * 2;
        for (int j = 1; j < dp[i].size() - 1; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1] * 2;
        }
    }

    string pre;
    stack<char> opens;
    char *alpha = new char[4]{'(', ')', '[', ']'};
    for (int i = 0; i < n * 2; i++) {
        for (int j = 0; j < 4; j++) {
            char c = alpha[j];
            bool correc = (c == '(' && opens.size() < n) || (c == ')' && !opens.empty() && opens.top() == '(') ||
                          (c == '[' && opens.size() < n) || (c == ']' && !opens.empty() && opens.top() == '[');

            if (correc) {
                ull count = dp[n * 2 - i - 1][opens.size() + (c == '(' || c == '[' ? 1 : -1)];

                if (count <= k) {
                    k -= count;
                } else {
                    pre += c;
                    if (c == '(' || c == '[') {
                        opens.push(c);
                    } else {
                        opens.pop();
                    }
                    break;
                }
            }
        }
    }

    cout << pre;
    return 0;
}