#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main()
{
  int n, r;
  cin >> n >> r;
  r--;

  vector<vector<int>> graph(n);
  vector<pair<int, int>> edges(n - 1);

  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    graph[u].push_back(i);
    graph[v].push_back(i);
    edges[i] = {u, v};
  }

  vector<int> parent(n, -1);
  function<void(int, int)> dfs = [&](int v, int p){
    for (int &e : graph[v]) {
      auto &edge = edges[e];
      if (edge.first == p || edge.second == p) continue;
      if (edge.second == v) {
        swap(edge.first, edge.second);
      }

      parent[edge.second] = e;
      dfs(edge.second, v);
    }
  };
  dfs(r, -1);

  vector<vector<int>> tree(n);
  for (int i = 0; i < n; i++) {
    if (i == r) continue;
    int e = parent[i];
    tree[edges[e].first].push_back(e);
  }

  vector<unsigned int> grandi(n, 0);
  function<void(int)> g = [&](int v){
    for (int &e : tree[v]) {
      auto[_, next] = edges[e];
      g(next);
      grandi[v] ^= grandi[next] + 1;
    }
  };
  g(r);

  if (grandi[r] == 0) {
    cout << 2 << endl;
    return 0;
  }

  cout << 1 << endl;
  int answer = -1;
  function<void(int, int)> find = [&](int e, unsigned int x) {
    auto[u, v] = edges[e];
    if ((grandi[u] ^ (grandi[v] + 1)) == x) {
      answer = e;
    }

    for (int i = 0; i < tree[v].size() && answer == -1; i++) {
      find(tree[v][i], (grandi[u] ^ (grandi[v] + 1) ^ x) - 1);
    }
  };

  for (int &e : tree[r]) {
    find(e, 0);
  }

  cout << answer + 1 << endl;

  return 0;
}