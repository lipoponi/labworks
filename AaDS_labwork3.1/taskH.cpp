#include <iostream>
#include <vector>
#include <algorithm>

#define fastIO do { std::cin.tie(nullptr); std::cout.tie(nullptr); std::ios::sync_with_stdio(false); } while (false);

typedef std::vector<std::vector<int>> graph_t;
graph_t graph;
std::vector<bool> used;

void dfs(int v, int &mv) {
    if (used[v]) {
        return;
    }
    used[v] = true;

    for (int u = 0; u != graph[v].size(); u++) {
        if (graph[v][u] <= mv) {
            dfs(u, mv);
        }
    }
}

void dfs2(int v, int &mv) {
    if (used[v]) {
        return;
    }
    used[v] = true;

    for (int u = 0; u != graph[v].size(); u++) {
        if (graph[u][v] <= mv) {
            dfs2(u, mv);
        }
    }
}

bool check(int mv) {
    used.assign(graph.size(), false);
    dfs(0, mv);
    if (std::count(used.begin(), used.end(), false)) return false;
    used.assign(graph.size(), false);
    dfs2(0, mv);
    return std::count(used.begin(), used.end(), false) == 0;
}

int main() {
    fastIO

#ifndef DEBUG
    std::freopen("avia.in", "r", stdin);
    std::freopen("avia.out", "w", stdout);
    fastIO
#endif

    int n;
    std::cin >> n;

    graph.assign(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
        }
    }

    int l = 0, r = 1000000090;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if (check(l)) {
        std::cout << l << std::endl;
    } else {
        std::cout << r << std::endl;
    }

    return 0;
}