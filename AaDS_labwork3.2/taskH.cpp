#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
#ifndef DEBUG
  freopen("game.in", "r+", stdin);
  freopen("game.out", "w+", stdout);
#endif

  int n, m, s;
  cin >> n >> m >> s;
  s--;

  vector<vector<int>> graph(n);
  vector<vector<int>> reversed(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    graph[u].push_back(v);
    reversed[v].push_back(u);
  }

  queue<int> wave;
  vector<bool> win(n, false);
  vector<int> cnt(n, 0);

  for (int i = 0; i < n; i++) {
    cnt[i] = graph[i].size();

    if (graph[i].empty()) {
      wave.push(i);
    }
  }

  while (cnt[s] != 0) {
    int current = wave.front();
    wave.pop();

    for (auto &prev : reversed[current]) {
      cnt[prev]--;
      if (!win[current]) {
        win[prev] = true;
      }

      if (cnt[prev] == 0) {
        wave.push(prev);
      }
    }
  }

  if (win[s]) {
    cout << "First player wins" << endl;
  } else {
    cout << "Second player wins" << endl;
  }
  return 0;
}