#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


struct Node {
    bool black = true;
    int count = 0, supCentroid = -1, prev;
    unordered_set<int> children, subCentroids;
    unordered_map<int, long long> supCentroidsDistance;
    unordered_map<int, int> between;
    vector<int> sups;

    int bCount = 0, wCount = 0;
    long long bSum = 0, wSum = 0;
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

int decomposition(int v, int prev, int parent) {
    nodes[v].prev = prev;

    int heavy = -1;
    for (int kid : nodes[v].children) {
        if (nodes[v].count < nodes[kid].count * 2 && (heavy == -1 || nodes[heavy].count < nodes[kid].count)) {
            heavy = kid;
        }
    }

    for (auto e : nodes[prev].supCentroidsDistance) {
        if (nodes[v].supCentroidsDistance.find(e.first) == nodes[v].supCentroidsDistance.end()) {
            nodes[v].supCentroidsDistance[e.first] = e.second + 1;
        }
    }

    if (heavy == -1) {
        nodes[v].supCentroidsDistance[v] = 0;

        for (int kid : nodes[v].children) {
            nodes[kid].children.erase(v);

            int kidCentroid = decomposition(kid, v, v);
            nodes[kidCentroid].supCentroid = v;
            nodes[v].subCentroids.insert(kidCentroid);
            if (kid == prev) nodes[v].between[parent] = kidCentroid;
        }

        return v;
    } else {
        nodes[v].count -= nodes[heavy].count;
        nodes[heavy].count += nodes[v].count;

        return decomposition(heavy, v, parent);
    }
}

inline int decomposition() {
    return decomposition(0, 0, 0); // TODO: check if it's correct
}


void preprocess(int v) {
    nodes[v].bCount = nodes[v].count;
    for (int next : nodes[v].subCentroids) {
        preprocess(next);
    }
}

long long calc(int v, int centroid, bool black) {
    long long sum = black ? nodes[v].bSum : nodes[v].wSum;
    int cnt = black ? nodes[v].bCount : nodes[v].wCount;

    for (int kid : nodes[v].subCentroids) {
        // TODO: it's not coreect condition
        if (nodes[v].between.find(centroid) == nodes[v].between.end()) continue;
        if (nodes[v].between[centroid] == kid) {
            sum -= calc(kid, v, black);
            sum += calc(kid, centroid, black);
            cnt -= black ? nodes[kid].bCount : nodes[kid].wCount;
        }
    }

    sum += cnt * nodes[v].supCentroidsDistance[centroid];
    return sum;
}


void go(int v) {
    for (int next : nodes[v].subCentroids) {
        go(next);
        nodes[v].bSum += calc(next, v, true);
    }
}

void change(int v) {
    bool black = !nodes[v].black;
    nodes[v].black = black;
    int p = v;

    while (p != -1) {
        nodes[p].bCount += black ? 1 : -1;
        nodes[p].wCount -= black ? 1 : -1;

        if (black) {
            nodes[p].bSum += nodes[v].supCentroidsDistance[p];
            nodes[p].wSum -= nodes[v].supCentroidsDistance[p];
        } else {
            nodes[p].bSum -= nodes[v].supCentroidsDistance[p];
            nodes[p].wSum += nodes[v].supCentroidsDistance[p];
        }

        p = nodes[p].supCentroid;
    }
}

long long get(int v) {
    bool black = nodes[v].black;

    long long sum = black ? nodes[v].bSum : nodes[v].wSum;
    int p = nodes[v].supCentroid, last = v;

    while (p != -1) {
        long long parentSum = black ? nodes[p].bSum : nodes[p].wSum;
        int parentCnt = black ? nodes[p].bCount : nodes[p].wCount;

        parentSum -= calc(last, p, black);
        parentCnt -= black ? nodes[last].bCount : nodes[last].wCount;

        sum += parentSum + nodes[v].supCentroidsDistance[p] * parentCnt;

        last = p;
        p = nodes[p].supCentroid;
    }

    return sum;
}


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif

    int n, m;
    cin >> n >> m;

    nodes.resize(n);

    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;

        nodes[v].children.insert(u);
        nodes[u].children.insert(v);
    }


    buildDfs();
    int root = decomposition();
    preprocess(root);
    go(root);

    for (int i = 0; i < m; i++) {
        int sum, v;
        cin >> sum >> v;
        sum--, v--;

        if (sum) {
            cout << get(v) << endl;
        } else {
            change(v);
        }
    }

    return 0;
}