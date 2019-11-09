#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

bool solve() {
  int n, m;
  if (!(cin >> n >> m)) {
    return false;
  }

  vector<unordered_set<int>> graph(n);
  vector<vector<int>> reversed(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    graph[u].insert(v);
    reversed[v].push_back(u);
  }

  vector<char> outcome(n, 'D');
  queue<int> wave;
  vector<bool> used(n, false);
  for (int i = 0; i < n; i++) {
    if (graph[i].empty()) {
      wave.push(i);
      outcome[i] = 'S';
    }
  }

  while (!wave.empty()) {
    int current = wave.front();
    wave.pop();
    if (used[current]) continue;
    used[current] = true;

    for (int &prev : reversed[current]) {
      graph[prev].erase(current);
      if (outcome[current] == 'S') {
        outcome[prev] = 'F';
        graph[prev].clear();
      }

      if (graph[prev].empty()) {
        if (outcome[prev] == 'D') {
          outcome[prev] = 'S';
        }

        wave.push(prev);
      }
    }
  }

  map<char, string> fullName;
  fullName['D'] = "DRAW";
  fullName['S'] = "SECOND";
  fullName['F'] = "FIRST";

  for (char &val : outcome) {
    cout << fullName[val] << endl;
  }

  return true;
}

int main() {
  while (solve()) {
    cout << endl;
  }
  return 0;
}