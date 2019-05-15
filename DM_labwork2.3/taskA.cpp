#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

typedef vector<unordered_map<char, unordered_set<int>>> Automaton;

bool check(Automaton nka, string input, int starting, int terminal) {
    queue<pair<int, int>> que;
    que.push({starting, 0});

    while (!que.empty()) {
        int state = que.front().first;
        int position = que.front().second;
        que.pop();

        if (state == terminal && position == input.size()) return true;
        if (input.size() <= position) continue;

        char symbol = input[position];
        if (nka[state].find(symbol) != nka[state].end()) {
            for (int next : nka[state][symbol]) {
                que.push({next, position + 1});
            }
        }
    }

    return false;
}

int main() {
#ifndef DEBUG
    freopen("automaton.in", "r+", stdin);
    freopen("automaton.out", "w+", stdout);
#endif

    int n;
    char S;
    cin >> n >> S;

    Automaton nka(27);
    for (int i = 0; i < n; i++) {
        char A;
        string arrow, rule;
        cin >> A >> arrow >> rule;

        int source = A - 'A', drain = 26;
        char symbol = rule[0];
        if (rule.size() == 2) drain = rule[1] - 'A';

        nka[source][symbol].insert(drain);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string w;
        cin >> w;

        if (check(nka, w, S - 'A', 26)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}