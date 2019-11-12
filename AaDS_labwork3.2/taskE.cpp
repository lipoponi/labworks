#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

const long long INF = 6000 * (long long)1e15;

using namespace std;

struct edge {
  int s, d;
  long long w;
};

int main()
{
  int n, m, s;
  cin >> n >> m >> s;
  s--;

  vector<edge> edges;
  vector<vector<int>> graph(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    a--, b--;

    edges.push_back({a, b, w});
    graph[a].push_back(b);
  }

  vector<vector<long long>> d(n, vector<long long>(n + 1, INF));
  vector<int> badass;
  d[s][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      d[j][i] = d[j][i - 1];
    }

    for (auto[u, v, w] : edges) {
      if (d[u][i - 1] == INF) continue;
      if (d[u][i-1] + w < d[v][i]) {
        if (i == n) {
          badass.push_back(v);
        }
        d[v][i] = d[u][i - 1] + w;
      }
    }
  }

  vector<bool> used(n, false);

  function<void(int)> dfs = [&](int v){
    if (used[v]) {
      return;
    }
    used[v] = true;

    for (int &next : graph[v]) {
      dfs(next);
    }
  };

  for (int &v : badass) {
    dfs(v);
  }

  vector<long long> answer(n, INF);

  for (int i = 0; i < n; i++) {
    for (auto &val : d[i]) {
      answer[i] = min(answer[i], val);
    }
  }

  for (int i = 0; i < n; i++) {
    if (used[i]) {
      cout << '-' << endl;
    } else if (answer[i] == INF) {
      cout << '*' << endl;
    } else {
      cout << answer[i] << endl;
    }
  }
  return 0;
}