#include <queue>
#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("problem2.in", "r+", stdin);
    freopen("problem2.out", "w+", stdout);
#endif

    string input;
    cin >> input;

    unsigned int n, m, k;
    cin >> n >> m >> k;

    set<unsigned int> terminals;
    for (int i = 0; i < k; i++) {
        unsigned int stateNo;
        cin >> stateNo;
        terminals.insert(stateNo - 1);
    }

    vector<map<char, set<unsigned int>>> nfaTransitions(n);
    for (int i = 0; i < m; i++) {
        unsigned int source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        source--;
        drain--;

        nfaTransitions[source][symbol].insert(drain);
    }


    set<unsigned int> activeStates;
    activeStates.insert(0);

    for (char symbol : input) {
        set<unsigned int> nextStates;
        for (auto state : activeStates) {
            nextStates.merge(set<unsigned int>(nfaTransitions[state][symbol]));
        }
        activeStates.clear();
        activeStates = nextStates;
    }

    for (auto currentState : activeStates) {
        if (terminals.find(currentState) != terminals.end()) {
            cout << "Accepts" << endl;
            return 0;
        }
    }

    cout << "Rejects" << endl;
    return 0;
}