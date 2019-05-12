#include <unordered_map>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("nfc.in", "r+", stdin);
    freopen("nfc.out", "w+", stdout);
#endif

    int n;
    char S;
    cin >> n >> S;

    unordered_map<char, unordered_set<string>> rulesMap;
    for (int i = 0; i < n; i++) {
        char A;
        string arrow, val;
        cin >> A >> arrow >> val;

        rulesMap[A].insert(val);
    }

    vector<pair<char, string>> rules;
    for (auto &f : rulesMap) {
        for (string s : f.second) {
            rules.emplace_back(f.first, s);
        }
    }

    string w;
    cin >> w;

    vector<vector<vector<unsigned int>>> dp(w.size() + 1);
    for (int i = 0; i <= w.size(); i++) {
        dp[i] = vector<vector<unsigned int>>(26, vector<unsigned int>(w.size(), 0));
    }


    for (auto &rule : rules) {
        if (rule.second.size() != 1) continue;

        for (int i = 0; i < w.size(); i++) {
            if (w[i] == rule.second[0]) {
                dp[1][rule.first - 'A'][i]++;
            }
        }
    }

    for (int k = 2; k <= w.size(); k++) {
        for (auto &rule : rules) {
            if (rule.second.size() != 2) continue;

            for (int i = 0; i <= w.size() - k; i++) {
                for (int j = 1; j < k; j++) {
                    unsigned long long A1 = dp[j][rule.second[0] - 'A'][i];
                    unsigned long long A2 = dp[k - j][rule.second[1] - 'A'][i + j];
                    dp[k][rule.first - 'A'][i] = (dp[k][rule.first - 'A'][i] + A1 * A2) % 1000000007;
                }
            }
        }
    }

    cout << dp[w.size()][S - 'A'][0] << endl;
    return 0;
}