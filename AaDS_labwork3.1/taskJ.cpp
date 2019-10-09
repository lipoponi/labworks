#include <iostream>
#include <vector>
#include <set>

const int INF = 1234567;

struct vertex {
    std::vector<std::pair<int, int>> edges;
};

std::set<std::pair<int, int>> keq;
std::vector<vertex> vertices;
std::vector<bool> used;

void addVertex(int v) {
    used[v] = true;

    for (int i = 0; i != vertices[v].edges.size(); i++) {
        keq.insert(vertices[v].edges[i]);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    vertices.resize(n);
    used.resize(n, false);

    for (int i = 0; i < m; i++) {
        int b, e, w;
        std::cin >> b >> e >> w;
        b--;
        e--;

        vertices[b].edges.emplace_back(w, e);
        vertices[e].edges.emplace_back(w, b);
    }

    addVertex(0);
    int count = 1;
    unsigned long long answer = 0;

    while (count < n) {
        while (!keq.empty() && used[keq.begin()->second]) {
            keq.erase(keq.begin());
        }
        auto it = keq.begin();
        auto idx = it->second;
        answer += it->first;

        addVertex(idx);
        count++;
    }

    std::cout << answer << std::endl;

    return 0;
}