#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;


int main() {
#ifndef DEBUG
    freopen("problem5.in", "r+", stdin);
    freopen("problem5.out", "w+", stdout);
#endif

    unsigned int n, m, k, l;
    cin >> n >> m >> k >> l;

    unordered_set<unsigned int> nkaTerminals;
    for (int i = 0; i < k; i++) {
        unsigned int vertexNo;
        cin >> vertexNo;
        nkaTerminals.insert(vertexNo - 1);
    }

    vector<unordered_map<char, set<unsigned int>>> nka(n);
    for (int i = 0; i < m; i++) {
        unsigned int source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        nka[source - 1][symbol].insert(drain - 1);
    }

    vector<unordered_map<unsigned int, unsigned int>> dka(1);
    unordered_set<unsigned int> dkaTerminals;
    map<set<unsigned int>, unsigned int> mapping;

    queue<set<unsigned int>> que;
    que.push({0});
    mapping[{0}] = 0;
    if (nkaTerminals.find(0) != nkaTerminals.end()) dkaTerminals.insert(0);

    while (!que.empty()) {
        set<unsigned int> sources = que.front();
        que.pop();

        for (char c = 'a'; c <= 'z'; c++) {
            set<unsigned int> drains;
            for (auto vertex : sources) {
                drains.merge(set<unsigned int>(nka[vertex][c]));
            }

            if (drains.empty()) continue;

            if (mapping.find(drains) == mapping.end()) {
                mapping[drains] = dka.size();
                dka.emplace_back();

                dka[mapping[sources]][mapping[drains]]++;

                for (auto vertex : drains) {
                    if (nkaTerminals.find(vertex) != nkaTerminals.end()) {
                        dkaTerminals.insert(mapping[drains]);
                    }
                }

                que.push(drains);
            } else {
                dka[mapping[sources]][mapping[drains]]++;
            }
        }
    }

    n = dka.size();
    vector<vector<unsigned long long>> dp(n, vector<unsigned long long>(l + 1));
    dp[0][0] = 1;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < n; j++) {
            for (auto next : dka[j]) {
                dp[next.first][i + 1] = (dp[next.first][i + 1] + dp[j][i] * next.second) % 1000000007;
            }
        }
    }

    unsigned long long ans = 0;
    for (auto vertex : dkaTerminals) {
        ans += dp[vertex][l];
    }

    cout << ans % 1000000007;
    return 0;
}