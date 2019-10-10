#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>

struct vertex;

typedef std::vector<vertex> graph_t;

std::vector<std::pair<int, int>> edges;
std::map<std::pair<int, int>, std::set<int>> mp;

struct vertex {
    std::set<int> edges;
};

class Condensation {
private:
    struct advanced_vertex {
        std::vector<int> edges;
        std::vector<int> inverted;

        int degI = 0, degO = 0;
        int tout = 0;
    };

    typedef std::vector<advanced_vertex> advanced_t;

    static advanced_t copy(const graph_t &input) {
        advanced_t result(input.size());

        for (int u = 0; u != input.size(); u++) {
            for (int e : input[u].edges) {
                auto[_, v] = edges[e];

                result[u].edges.push_back(e);
                result[u].degO++;

                result[v].inverted.push_back(e);
                result[v].degI++;
            }
        }

        return result;
    }

    static void timeDfs(int v, int &time, advanced_t &graph, std::vector<bool> &used) {
        if (used[v]) {
            return;
        }
        used[v] = true;

        ++time;

        for (int e : graph[v].inverted) {
            auto[next, _] = edges[e];
            timeDfs(next, time, graph, used);
        }

        graph[v].tout = ++time;
    }

    static void timeDfs(advanced_t &graph) {
        int time = 0;
        std::vector<bool> used(graph.size(), false);

        for (int i = 0; i != graph.size(); i++) {
            timeDfs(i, time, graph, used);
        }
    }

    static void componentDfs(int v, const int &color, const advanced_t &graph, std::vector<int> &marks) {
        if (marks[v] != 0) {
            return;
        }
        marks[v] = color;

        for (int e : graph[v].edges) {
            auto[_, next] = edges[e];
            componentDfs(next, color, graph, marks);
        }
    }

    static graph_t componentDfs(const advanced_t &graph) {
        std::vector<std::pair<int, int>> outTimePairs(graph.size());
        for (int i = 0; i != graph.size(); i++) {
            outTimePairs[i] = {graph[i].tout, i};
        }
        std::sort(outTimePairs.rbegin(), outTimePairs.rend());

        std::vector<int> marks(graph.size(), 0);
        int color = 0;

        for (auto p : outTimePairs) {
            if (marks[p.second] != 0) continue;

            color++;
            componentDfs(p.second, color, graph, marks);
        }

        graph_t result(color);

        for (int u = 0; u != graph.size(); u++) {
            for (int e : graph[u].edges) {
                auto[_, v] = edges[e];

                int uColor = marks[u] - 1;
                int vColor = marks[v] - 1;
                if (uColor == vColor) continue;

                mp[{uColor, vColor}].insert(e);
                result[uColor].edges.insert(vColor);
            }
        }

        return result;
    }

public:
    static graph_t process(const graph_t &input) {
        advanced_t graph = copy(input);
        timeDfs(graph);

        graph_t result = componentDfs(graph);

        return result;
    }
};

void dfs(int v, std::vector<bool> &used, std::vector<std::set<int>> &graph) {
    if (used[v]) {
        return;
    }
    used[v] = true;

    for (int e : graph[v]) {
        int y = edges[e].second;
        if (v == y) {
            edges[e] = {edges[e].second, edges[e].first};
        }

        dfs(edges[e].second, used, graph);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::set<int>> gr(n);
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int b, e;
        std::cin >> b >> e;
        b--;
        e--;

        edges[i] = {b, e};
        gr[b].insert(i);
        gr[e].insert(i);
    }

    std::vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        dfs(i, used, gr);
    }

    graph_t graph(n);
    for (int i = 0; i != gr.size(); i++) {
        for (int e : gr[i]) {
            int u = edges[e].first;
            if (u == i) graph[i].edges.insert(e);
        }
    }

    graph_t result = Condensation::process(graph);
    std::set<int> answer;

    for (int u = 0; u != result.size(); u++) {
        for (int v : result[u].edges) {
            answer.merge(mp[{u, v}]);
        }
    }

    std::cout << answer.size() << std::endl;

    for (int e : answer) {
        std::cout << e + 1 << std::endl;
    }

    return 0;
}