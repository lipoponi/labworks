#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    for (auto &row : graph) {
        for (auto &c : row) {
            cin >> c;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                graph[u][v] = min(graph[u][v], graph[u][i] + graph[i][v]);
                graph[v][u] = min(graph[v][u], graph[v][i] + graph[i][u]);
            }
        }
    }

    for (auto &row : graph) {
        for (int &w : row) {
            cout << w << " ";
        }
        cout << endl;
    }
    return 0;
}