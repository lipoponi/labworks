#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>

using namespace std;

typedef vector<vector<int>> Automaton;


class Hopcroft {
private:
    vector<char> marks;
    vector<vector<int>> lr, rl;
    vector<unordered_set<int>> P;
    vector<int> Class;
    vector<vector<vector<int>>> Inv;
    Automaton dka;
    vector<bool> terminals;


    void mark();

    void mark(int vertex, int level, vector<vector<int>> &ways);

    void findClasses();

    void build(Automaton &newDka, vector<bool> &newTerminals);

public:
    void putMinified(Automaton &newDka, vector<bool> &newTerminals);

    Hopcroft(Automaton dka, vector<bool> terminals);
};

Hopcroft::Hopcroft(Automaton dka, vector<bool> terminals) {
    this->dka = dka;
    this->terminals = terminals;

    marks.resize(dka.size(), 0);
    lr.resize(dka.size());
    rl.resize(dka.size());

    for (int i = 0; i < dka.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            auto l = dka[i][c - 'a'];
            if (l == UINT_FAST16_MAX) continue;
            lr[i].push_back(l);
            rl[l].push_back(i);
        }
    }

    mark();
    Inv.resize(dka.size(), vector<vector<int>>(26));

    for (int i = 0; i < dka.size(); i++) {
        if (marks[i] != 2) continue;
        for (char c = 'a'; c <= 'z'; c++) {
            auto l = dka[i][c - 'a'];
            if (l == UINT_FAST16_MAX) continue;
            if (marks[l] != 2) continue;
            Inv[l][c - 'a'].push_back(i);
        }
    }
}

void Hopcroft::mark() {
    mark(0, 1, lr);
    for (int i = 0; i < terminals.size(); i++) {
        if (terminals[i]) mark(i, 2, rl);
    }
}

void Hopcroft::mark(int vertex, int level, vector<vector<int>> &ways) {
    if (marks[vertex] != level - 1) return;
    marks[vertex] = level;

    for (auto &next : ways[vertex]) {
        if (marks[next] == level - 1) mark(next, level, ways);
    }
}

void Hopcroft::findClasses() {
    P.resize(2);
    Class.resize(dka.size(), -1);

    for (int i = 0; i < dka.size(); i++) {
        if (marks[i] != 2) continue;
        if (terminals[i]) {
            P[0].insert(i);
            Class[i] = 0;
        } else {
            P[1].insert(i);
            Class[i] = 1;
        }
    }

    if (P[1].empty()) P.resize(1);

    queue<pair<int, char>> Queue;
    unordered_map<int, vector<int>> Involved;

    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 0; i < P.size(); i++) {
            Queue.push({i, c});
        }
    }

    while (!Queue.empty()) {
        auto C = P[Queue.front().first];
        auto a = Queue.front().second;
        Queue.pop();
        Involved.clear();
        for (auto q : C) {
            for (auto r : Inv[q][a - 'a']) {
                if (marks[r] != 2) continue;
                int i = Class[r];
                Involved[i].push_back(r);
            }
        }

        for (auto &record : Involved) {
            if (record.second.size() < P[record.first].size()) {
                int j = P.size();
                P.emplace_back();

                for (auto r : record.second) {
                    P[record.first].erase(r);
                    P[j].insert(r);
                }

                if (P.back().empty()) {
                    P.pop_back();
                    continue;
                }

                if (P[record.first].size() < P[j].size()) {
                    swap(P[record.first], P[j]);
                }

                for (auto r : P[j]) {
                    Class[r] = j;
                }

                for (char c = 'a'; c <= 'z'; c++) {
                    Queue.push({j, c});
                }
            }
        }
    }
}

void Hopcroft::build(Automaton &newDka, vector<bool> &newTerminals) {
    newDka.clear();
    newTerminals.clear();

    if (Class[0] != 0) {
        int s = Class[0];
        swap(P[0], P[s]);
        for (int i : P[0]) Class[i] = 0;
        for (int i : P[s]) Class[i] = s;
    }

    newDka.resize(P.size(), vector<int>(26, UINT_FAST16_MAX));
    newTerminals.resize(P.size(), false);

    for (int i = 0; i < P.size(); i++) {
        int vertex = *P[i].begin();
        if (terminals[vertex]) newTerminals[i] = true;
        for (char c = 'a'; c <= 'z'; c++) {
            if (dka[vertex][c - 'a'] == UINT_FAST16_MAX) continue;
            if (marks[dka[vertex][c - 'a']] != 2) continue;
            newDka[i][c - 'a'] = Class[dka[vertex][c - 'a']];
        }
    }
}

void Hopcroft::putMinified(Automaton &newDka, vector<bool> &newTerminals) {
    if (marks[0] == 2) {
        findClasses();
        build(newDka, newTerminals);
    } else {
        newDka.clear();
        terminals.clear();
    }
}


void readAutomaton(Automaton &dka, vector<bool> &terminals) {
    dka.clear();
    terminals.clear();

    int n, m, k;
    cin >> n >> m >> k;

    dka.resize(n, vector<int>(26, UINT_FAST16_MAX));
    terminals.resize(n, false);

    for (int i = 0; i < k; i++) {
        int vertexNo;
        cin >> vertexNo;
        terminals[vertexNo - 1] = true;
    }

    for (int i = 0; i < m; i++) {
        int source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        dka[source - 1][symbol - 'a'] = drain - 1;
    }
}

Automaton dka1, dka2;
vector<bool> terminals1, terminals2;
vector<bool> used1, used2;

bool isomorphic(int p1, int p2) {
    if (used1[p1] && used2[p2]) return true;
    if (used1[p1] || used2[p2]) {
        used1[p1] = used2[p2] = true;
        return false;
    }
    used1[p1] = used2[p2] = true;
    if (terminals1[p1] != terminals2[p2]) return false;

    for (char c = 'a'; c <= 'z'; c++) {
        if ((dka1[p1][c - 'a'] == UINT_FAST16_MAX) && (dka2[p2][c - 'a'] == UINT_FAST16_MAX)) continue;
        else if ((dka1[p1][c - 'a'] == UINT_FAST16_MAX) || (dka2[p2][c - 'a'] == UINT_FAST16_MAX)) return false;
        else if (!isomorphic(dka1[p1][c - 'a'], dka2[p2][c - 'a'])) return false;
    }

    return true;
}

int main() {
#ifndef DEBUG
    freopen("equivalence.in", "r+", stdin);
    freopen("equivalence.out", "w+", stdout);
#endif

    readAutomaton(dka1, terminals1);
    readAutomaton(dka2, terminals2);

    used1.resize(dka1.size());
    used2.resize(dka2.size());

    Hopcroft algo1(dka1, terminals1);
    Hopcroft algo2(dka2, terminals2);

    algo1.putMinified(dka1, terminals1);
    algo2.putMinified(dka2, terminals2);

    if (terminals1.size() != terminals2.size() || dka1.size() != dka2.size()) {
        cout << "NO" << endl;
        return 0;
    }

    if (isomorphic(0, 0)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}