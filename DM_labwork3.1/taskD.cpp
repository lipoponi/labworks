#include <iostream>
#include <vector>
#include <cstdio>
#include <functional>
#include <list>
#include <set>

using namespace std;

int main() {
#ifndef DEBUG
  freopen("guyaury.in", "r+", stdin);
  freopen("guyaury.out", "w+", stdout);
#endif

  int n;
  cin >> n;

  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }

  string line;
  getline(cin, line);

  vector<set<int>> graph(n);

  for (int i = 0; i < n; i++) {
    getline(cin, line);
    for (int j = 0; j != line.size(); j++) {
      if (line[j] == '1') {
        graph[i].insert(j);
      } else {
        graph[j].insert(i);
      }
    }
  }

  list<int> path;

  for (int i = 0; i < n; i++) {
    auto it = path.begin();
    while (it != path.end() && graph[*it].count(i) != 0) {
      it++;
    }
    path.insert(it, i);
  }

#ifdef DEBUG
  for (int val : path) {
    cout << val << " ";
  }

  cout << endl;
#endif

  list<int> circle;

  circle.push_back(path.front());
  path.pop_front();
  circle.push_back(path.front());
  path.pop_front();

  auto it = path.begin();
  auto e = path.end();
  while (it != path.end()) {
    if (graph[*it].count(circle.front())) {
      e = it;
    }
    it++;
  }

  if (e != path.end()) {
    e++;
    while (path.begin() != e) {
      circle.push_back(path.front());
      path.pop_front();
    }
  }

  auto pit = path.begin();
  while (pit != path.end()) {
    auto it = circle.begin();
    while (it != circle.end() && graph[*pit].count(*it) == 0) {
      it++;
    }

    pit++;
    if (it != circle.end()) {
      while (path.begin() != pit) {
        circle.insert(it, path.front());
        path.pop_front();
      }
    }
  }

  for (auto val : circle) {
    cout << val + 1 << " ";
  }
  return 0;
}