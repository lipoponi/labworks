#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


struct Node {
    int count = 0, supCentroid = -1;
    unordered_set<int> children, subCentroids;
    unordered_map<int, int> supCentroidsDistance;
};

vector<Node> nodes;


void buildDfs(int v = 0) {
    nodes[v].count = 1;
    for (int next : nodes[v].children) {
        if (nodes[next].count != 0) continue;
        buildDfs(next);
        nodes[v].count += nodes[next].count;
    }
}

int decomposition(int v, int prev) {
    int heavy = -1;
    for (int kid : nodes[v].children) {
        if (nodes[v].count < nodes[kid].count * 2 && (heavy == -1 || nodes[heavy].count < nodes[kid].count)) {
            heavy = kid;
        }
    }

    for (auto e : nodes[prev].supCentroidsDistance) {
        if (nodes[v].supCentroidsDistance.find(e.first) == nodes[v].supCentroidsDistance.end()) {
            nodes[v].supCentroidsDistance[e.first] = e.second + 1;
        } else {
            nodes[v].supCentroidsDistance[e.first] = min(nodes[v].supCentroidsDistance[e.first], e.second + 1);
        }
    }

    if (heavy == -1) {
        nodes[v].supCentroidsDistance[v] = 0;

        for (int kid : nodes[v].children) {
            nodes[kid].children.erase(v);

            int kidCentroid = decomposition(kid, v);
            nodes[kidCentroid].supCentroid = v;
            nodes[v].subCentroids.insert(kidCentroid);
        }

        return v;
    } else {
        nodes[v].count -= nodes[heavy].count;
        nodes[heavy].count += nodes[v].count;

        return decomposition(heavy, v);
    }
}

inline int decomposition() {
    return decomposition(0, 0);
}


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif

    int n;
    cin >> n;

    nodes.resize(n);

    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;

        nodes[v].children.insert(u);
        nodes[u].children.insert(v);
    }


    buildDfs();
    decomposition();

    for (Node &v : nodes) {
        cout << v.supCentroid + 1 << " ";
    }
    
    return 0;
}