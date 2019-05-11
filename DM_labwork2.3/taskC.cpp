#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

vector<bool> getSeen(vector<pair<char, string>> &rules) {
    vector<bool> seen(26, false);

    for (auto &rule : rules) {
        seen[rule.first - 'A'] = true;
        for (char &c : rule.second) {
            if ('A' <= c && c <= 'Z') seen[c - 'A'] = true;
        }
    }

    return seen;
}

void dfsReachable(char A, vector<bool> &reachable, vector<pair<char, string>> &rules) {
    if (reachable[A - 'A']) return;
    reachable[A - 'A'] = true;

    for (auto &rule : rules) {
        if (rule.first == A) {
            for (char c : rule.second) {
                if ('A' <= c && c <= 'Z') {
                    dfsReachable(c, reachable, rules);
                }
            }
        }
    }
}


int main() {
#ifndef DEBUG
    freopen("useless.in", "r+", stdin);
    freopen("useless.out", "w+", stdout);
#endif

    int n;
    char S;
    cin >> n >> S;


    vector<pair<char, string>> rules;

    for (int i = 0; i < n; i++) {
        char A;
        string arrow, tmp;
        cin >> A >> arrow;
        getline(cin, tmp);

        string rule;
        for (char &c : tmp) if (c != ' ') rule.push_back(c);

        rules.emplace_back(A, rule);
    }

    vector<bool> seen = getSeen(rules);

    int lastSize = -1;
    set<char> generating;

    while (lastSize != generating.size()) {
        lastSize = generating.size();

        for (auto &rule : rules) {
            bool gen = true;
            for (char &c : rule.second) {
                if ('A' <= c && c <= 'Z' && generating.find(c) == generating.end()) {
                    gen = false;
                }
            }
            if (gen) generating.insert(rule.first);
        }
    }

    vector<pair<char, string>> newRules;

    for (auto &rule : rules) {
        if (generating.find(rule.first) == generating.end()) continue;

        bool gen = true;
        for (char &c : rule.second) {
            if ('A' <= c && c <= 'Z' && generating.find(c) == generating.end()) {
                gen = false;
            }
        }
        if (gen) newRules.push_back(rule);
    }

    vector<bool> newSeen = getSeen(newRules);

    vector<bool> reachable(26, false);
    dfsReachable(S, reachable, newRules);

    set<int> answer;
    for (int i = 0; i < 26; i++) {
        if (seen[i]) {
            if (!newSeen[i] || (newSeen[i] && !reachable[i])) answer.insert(i + 'A');
        }
    }

    for (char c : answer) {
        cout << c << " ";
    }
    return 0;
}