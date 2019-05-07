#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<int> terminals1, terminals2;
vector<unordered_map<char, int>> graph1, graph2;
vector<bool> used1, used2;

bool isomorphic(int p1, int p2) {
    if (used1[p1] && used2[p2]) return true;
    if (used1[p1] || used2[p2]) {
        used1[p1] = used2[p2] = true;
        return false;
    }
    used1[p1] = used2[p2] = true;
    if ((terminals1.find(p1) != terminals1.end()) != (terminals2.find(p2) != terminals2.end())) return false;

    for (auto &next : graph1[p1]) {
        if (graph2[p2].find(next.first) == graph2[p2].end()) return false;
        if (!isomorphic(next.second, graph2[p2][next.first])) return false;
    }

    return true;
}

void read(unordered_set<int> &terminals, vector<unordered_map<char, int>> &graph, vector<bool> &used) {
    unsigned int n, m, k;
    cin >> n >> m >> k;

    graph.resize(n);
    used.resize(n, false);

    for (int i = 0; i < k; i++) {
        unsigned int vertexNo;
        cin >> vertexNo;
        terminals.insert(vertexNo - 1);
    }

    for (int i = 0; i < m; i++) {
        unsigned int source, drain;
        char symbol;
        cin >> source >> drain >> symbol;

        source--;
        drain--;

        graph[source][symbol] = drain;
    }
}

int main() {
#ifndef DEBUG
    freopen("isomorphism.in", "r+", stdin);
    freopen("isomorphism.out", "w+", stdout);
#endif

    read(terminals1, graph1, used1);
    read(terminals2, graph2, used2);

    if (terminals1.size() != terminals2.size() || graph1.size() != graph2.size()) {
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