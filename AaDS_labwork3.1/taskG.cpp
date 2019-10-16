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

    static std::vector<int> componentDfs(const advanced_t &graph) {
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

        return marks;

//        graph_t result(color);
//
//        for (int u = 0; u != graph.size(); u++) {
//            for (int e : graph[u].edges) {
//                auto [_, v] = edges[e];
//
//                int uColor = marks[u] - 1;
//                int vColor = marks[v] - 1;
//                if (uColor == vColor) continue;
//
//                mp[{uColor, vColor}].insert(e);
//                result[uColor].edges.insert(vColor);
//            }
//        }
//
//        return result;
    }

public:
    static std::vector<int> process(const graph_t &input) {
        advanced_t graph = copy(input);
        timeDfs(graph);

        return componentDfs(graph);

//        graph_t result = componentDfs(graph);
//
//        return result;
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
    edges.resize(m);
    graph_t graph(n * 2);

    std::map<std::string, int> names;
    std::vector<std::string> manes(n);
    for (int i = 0; i < n; i++) {
        std::string tmp;
        std::cin >> tmp;
        names[tmp] = names.size();
        manes[i] = tmp;
    }

    for (int i = 0; i < m; i++) {
        char a, b;
        std::string aname, bname, arrow;
        std::cin >> a >> aname >> arrow >> b >> bname;

        int av = names[aname] * 2 + (a == '+');
        int na = names[aname] * 2 + (a != '+');
        int bv = names[bname] * 2 + (b == '+');
        int nb = names[bname] * 2 + (b != '+');

        edges[i] = {av, bv};
        graph[nb].edges.insert(edges.size());
        edges.emplace_back(nb, na);
        graph[av].edges.insert(i);
    }

    std::vector<int> marks = Condensation::process(graph);
    std::vector<std::string> result;

    for (int i = 0; i < n; i++) {
        if (marks[i * 2] == marks[i * 2 + 1]) {
            std::cout << -1 << std::endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (marks[i * 2 + 1] < marks[i * 2]) {
            result.push_back(manes[i]);
        }
    }

    std::cout << result.size() << std::endl;

    for (std::string &s : result) {
        std::cout << s << std::endl;
    }

    return 0;
}