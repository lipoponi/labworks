#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

using namespace std;

vector<int> g;
vector<vector<int>> graph;
vector<vector<int>> reversed;
vector<set<int>> mex_helper;

void grandi(int v) {
  if (g[v] != -1) {
    return;
  }

  for (int &next : graph[v]) {
    grandi(next);
  }

  int prev = -1;
  for (auto it = mex_helper[v].begin(); it != mex_helper[v].end(); it++) {
    if (*it != prev + 1) {
      g[v] = prev + 1;
      break;
    }

    prev = *it;
  }

  if (mex_helper[v].empty()) {
    g[v] = 0;
  }

  if (g[v] == -1) {
    g[v] = prev + 1;
  }

  for (int &pre : reversed[v]) {
    mex_helper[pre].insert(g[v]);
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  g.assign(n, -1);
  graph.resize(n);
  reversed.resize(n);
  mex_helper.resize(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    graph[u].push_back(v);
    reversed[v].push_back(u);
  }

  for (int i = 0; i < n; i++) {
    grandi(i);
    cout << g[i] << endl;
  }
  return 0;
}