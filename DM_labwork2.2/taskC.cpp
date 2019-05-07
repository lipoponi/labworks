#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <map>

using namespace std;

const unsigned long long modul = 1000000007L;

vector<unsigned long long> counts;
vector<map<unsigned int, set<char>>> graph;
vector<set<unsigned int>> hhhh;
vector<char> color;
vector<char> useful;

unsigned long long getCount(unsigned int node) {
    if (useful[node] != 2) return counts[node] = 0;
    if (counts[node] != 0) return counts[node];

    unsigned long long sum = 0;
    for (auto &next : graph[node]) {
        sum = (sum + next.second.size() * getCount(next.first)) % modul;
    }
    return counts[node] = sum;
}

void mark1(unsigned int node) {
    if (useful[node] != 0) return;
    useful[node] = 1;
    for (auto next : hhhh[node]) {
        if (useful[next] != 0) continue;
        mark1(next);
    }
}

void mark2(unsigned int node) {
    if (useful[node] != 1) return;
    useful[node] = 2;
    for (auto &next : graph[node]) {
        if (useful[next.first] != 1) continue;
        mark2(next.first);
    }
}

bool hasCycle(unsigned int node) {
    if (color[node] != 'w') return color[node] == 'g';

    color[node] = 'g';
    for (auto &next : hhhh[node]) {
        if (useful[next] != 2) continue;
        if (hasCycle(next)) return true;
    }
    color[node] = 'b';

    return false;
}

int main() {
#ifndef DEBUG
    freopen("problem3.in", "r+", stdin);
    freopen("problem3.out", "w+", stdout);
#endif

    unsigned int n, m, k;
    cin >> n >> m >> k;

    color.resize(n, 'w');
    counts.resize(n, 0);
    counts[0] = 1;
    graph.resize(n);
    hhhh.resize(n);
    useful.resize(n, 0);

    vector<unsigned int> terminals(k);
    for (int i = 0; i < k; i++) {
        unsigned int nodeNo;
        cin >> nodeNo;
        terminals[i] = nodeNo - 1;
    }


    for (int i = 0; i < m; i++) {
        unsigned int source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        source--;
        drain--;

        graph[drain][source].insert(symbol);
        hhhh[source].insert(drain);
    }

    mark1(0);
    for (auto node : terminals) {
        mark2(node);
    }

    if (hasCycle(0)) {
        cout << -1 << endl;
        return 0;
    }

    unsigned long long ans = 0;
    for (auto node : terminals) {
        ans = (ans + getCount(node)) % modul;
    }
    cout << ans << endl;
    return 0;
}