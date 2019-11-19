#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>

using namespace std;

int main() {
#ifndef DEBUG
  freopen("fullham.in", "r+", stdin);
  freopen("fullham.out", "w+", stdout);
#endif

  size_t n;
  cin >> n;
  string line;
  getline(cin, line);

  vector<vector<bool>> graph(n, vector<bool>(n, false));

  for (size_t i = 0; i < n; i++) {
    getline(cin, line);
    for (size_t j = 0; j < line.size(); j++) {
      graph[i][j] = graph[j][i] = (line[j] == '1');
    }
  }

  deque<int> que;
  for (size_t i = 0; i < n; i++) {
    que.push_back(i);
  }

  for (size_t j = 0; j < n * (n - 1); j++) {
    if (!graph[que[0]][que[1]]) {
      for (size_t i = 2; i < n - 1; i++) {
        if (graph[que[0]][que[i]] && graph[que[1]][que[i + 1]]) {
          reverse(que.begin() + 1, que.begin() + i + 1);
          break;
        }
      }
    }

    que.push_back(que.front());
    que.pop_front();
  }

  for (size_t i = 0; i < n; i++) {
    cout << que[i] + 1 << " ";
  }
  return 0;
}