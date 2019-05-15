#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("epsilon.in", "r+", stdin);
    freopen("epsilon.out", "w+", stdout);
#endif

    int n;
    char S;
    cin >> n >> S;

    set<pair<char, string>> rules;
    for (int i = 0; i < n; i++) {
        char A;
        string arrow, tmp, rule;
        cin >> A >> arrow;
        getline(cin, tmp);
        for (char &c : tmp) if (c != ' ') rule.push_back(c);

        rules.insert({A, rule});
    }

    set<char> answer;
    int lastSize = -1;

    while (lastSize != answer.size()) {
        lastSize = answer.size();

        for (auto &rule : rules) {
            char A = rule.first;
            string symbols = rule.second;

            bool eps = true;
            for (auto &c : symbols) {
                if (answer.find(c) == answer.end()) {
                    eps = false;
                    break;
                }
            }
            if (eps) answer.insert(A);
        }
    }

    for (auto &c : answer) {
        cout << c << " ";
    }
    return 0;
}