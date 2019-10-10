#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

struct vertex;

typedef std::vector<vertex> graph_t;

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
            for (int v : input[u].edges) {
                result[u].edges.push_back(v);
                result[u].degO++;

                result[v].inverted.push_back(u);
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

        for (int next : graph[v].inverted) {
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

    static void
    componentDfs(int v, const unsigned int &color, const advanced_t &graph, std::vector<unsigned int> &marks) {
        if (marks[v] != 0) {
            return;
        }
        marks[v] = color;

        for (int next : graph[v].edges) {
            componentDfs(next, color, graph, marks);
        }
    }

    static graph_t componentDfs(const advanced_t &graph) {
        std::vector<std::pair<int, int>> outTimePairs(graph.size());
        for (int i = 0; i != graph.size(); i++) {
            outTimePairs[i] = {graph[i].tout, i};
        }
        std::sort(outTimePairs.rbegin(), outTimePairs.rend());

        std::vector<unsigned int> marks(graph.size(), 0);
        int color = 0;

        for (auto p : outTimePairs) {
            if (marks[p.second] != 0) continue;

            color++;
            componentDfs(p.second, color, graph, marks);
        }

        graph_t result(color);

        for (int u = 0; u != graph.size(); u++) {
            for (int v : graph[u].edges) {
                int uColor = marks[u];
                int vColor = marks[v];
                if (uColor == vColor) continue;
                result[uColor - 1].edges.insert(vColor - 1);
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

int main() {
    int n, m;
    std::cin >> n >> m;

    graph_t graph(n);
    for (int i = 0; i < m; i++) {
        int b, e;
        std::cin >> b >> e;
        b--;
        e--;

        graph[b].edges.insert(e);
    }

    graph_t result = Condensation::process(graph);
    unsigned long long answer = 0;
    for (vertex &v : result) {
        answer += v.edges.size();
    }

    std::cout << answer << std::endl;

    return 0;
}