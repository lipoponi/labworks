#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> graph(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 100000) graph[i][j] = UINT32_MAX;
            if (i == j && graph[i][j] < 0) {
                cout << "YES" << endl;
                cout << 1 << endl << i + 1 << endl;
                return 0;
            }
        }
    }

    vector<vector<long long>> copy(graph);

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                graph[u][v] = min(graph[u][v], graph[u][i] + graph[i][v]);
                graph[v][u] = min(graph[v][u], graph[v][i] + graph[i][u]);

                if (u == v && graph[u][u] < 0) {
                    cout << "YES" << endl;

                    int sp = u;
                    vector<int> path(1, sp);
                    while (path.back() != i) {
                        for (int x = 0; x < n; x++) {
                            if (graph[sp][i] == copy[sp][i]) {
                                path.push_back(i);
                                sp = i;
                                break;
                            }
                            if (graph[sp][i] == copy[sp][x] + graph[x][i]) {
                                path.push_back(x);
                                sp = x;
                                break;
                            }
                        }
                    }
                    while (path.back() != u) {
                        for (int x = 0; x < n; x++) {
                            if (graph[sp][u] == copy[sp][u]) {
                                path.push_back(u);

                                break;
                            }
                            if (graph[sp][u] == copy[sp][x] + graph[x][u]) {
                                path.push_back(x);
                                sp = x;
                                break;
                            }
                        }
                    }

                    path.pop_back();
                    cout << path.size() << endl;
                    for (int &val : path) {
                        cout << val + 1 << " ";
                    }
                    return 0;
                }
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}