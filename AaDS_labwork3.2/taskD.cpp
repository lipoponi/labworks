#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
  int n, m, k, s;
  cin >> n >> m >> k >> s;
  s--;

  vector<vector<pair<int, int>>> graph(n);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--, b--;

    graph[a].emplace_back(b, w);
  }

  queue<pair<unordered_map<int, int>, queue<int>>> bfsq;
  unordered_map<int, int> init_lens;
  queue<int> init_layer({s});
  init_lens[s] = 0;

  bfsq.push({init_lens, init_layer});

  for (int i = 0; i < k; i++) {
    auto&[clens, clayer] = bfsq.front();
    unordered_map<int, int> parents;
    unordered_map<int, int> nlens;

    while (!clayer.empty()) {
      int v = clayer.front();
      clayer.pop();

      for (auto[dest, weight] : graph[v]) {
        if (nlens.find(dest) == nlens.end() || clens[v] + weight < nlens[dest]) {
          nlens[dest] = clens[v] + weight;
          parents[dest] = v;
        }
      }
    }

    bfsq.pop();
    bfsq.emplace(std::move(nlens), queue<int>());

    for (auto[nxt, _] : parents) {
      bfsq.back().second.push(nxt);
    }
  }

  auto[lens, _] = bfsq.front();
  for (int i = 0; i < n; i++) {
    if (lens.find(i) != lens.end()) {
      cout << lens[i] << endl;
    } else {
      cout << -1 << endl;
    }
  }
  return 0;
}