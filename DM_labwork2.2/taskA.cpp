#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("problem1.in", "r+", stdin);
    freopen("problem1.out", "w+", stdout);
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

    vector<map<char, unsigned int>> dfaStates(n);
    for (int i = 0; i < m; i++) {
        unsigned source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        source--;
        drain--;

        dfaStates[source][symbol] = drain;
    }


    unsigned int state = 0;
    for (char currentSymbol : input) {
        auto currentTransitions = dfaStates[state];
        if (currentTransitions.find(currentSymbol) == currentTransitions.end()) {
            cout << "Rejects" << endl;
            return 0;
        }

        state = currentTransitions[currentSymbol];
    }

    if (terminals.find(state) == terminals.end()) {
        cout << "Rejects" << endl;
    } else {
        cout << "Accepts" << endl;
    }
    return 0;
}