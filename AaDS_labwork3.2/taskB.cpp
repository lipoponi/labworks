#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#define INF (INT32_MAX * 16LL)

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, long long>>> graph(n);
  for (int i = 0; i < m; i++) {
    int s, d;
    long long w;
    cin >> s >> d >> w;
    s--, d--;

    graph[s].emplace_back(d, w);
    graph[d].emplace_back(s, w);
  }

  vector<long long> answer(n, INF);
  multiset<pair<long long, int>> pupa;
  answer[0] = 0;

  for (int i = 0; i != answer.size(); i++) {
    pupa.insert({answer[i], i});
  }

  for (int k = 0; k < n; k++) {
    auto cit = pupa.begin();
    int current = cit->second;
    pupa.erase(cit);

    if (answer[current] == INF) {
      break;
    }

    for (auto &edge : graph[current]) {
      auto[dest, weight] = edge;

      if (answer[current] + weight < answer[dest]) {
        auto it = pupa.find({answer[dest], dest});
        pupa.erase(it);
        pupa.insert({answer[current] + weight, dest});
        answer[dest] = answer[current] + weight;
      }
    }
  }

  for (auto &val : answer) {
    cout << val << " ";
  }
  return 0;
}