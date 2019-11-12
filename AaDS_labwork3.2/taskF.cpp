#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#define INF INT64_MAX

using namespace std;

typedef vector<vector<pair<int, unsigned long long>>> graph_t;

vector<unsigned long long> dijkstra(graph_t &graph, int start) {
  vector<unsigned long long> answer(graph.size(), INF);
  multiset<pair<unsigned long long, int>> pupa;
  answer[start] = 0;

  for (int i = 0; i != answer.size(); i++) {
    pupa.insert({answer[i], i});
  }

  for (int k = 0; k != graph.size(); k++) {
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
    if (val == INF) {
      val = 0;
    }
  }

  return answer;
}

int main() {
  int n, m;
  cin >> n >> m;

  graph_t graph(n);
  for (int i = 0; i < m; i++) {
    int s, d;
    unsigned long long w;
    cin >> s >> d >> w;
    s--, d--;

    graph[s].emplace_back(d, w);
    graph[d].emplace_back(s, w);
  }

  int a, b, c;
  cin >> a >> b >> c;
  a--, b--, c--;

  auto sa = dijkstra(graph, a);
  auto sb = dijkstra(graph, b);
  auto sc = dijkstra(graph, c);

  unsigned long long ab = sa[b];
  unsigned long long bc = sb[c];
  unsigned long long ca = sc[a];

  if (!ab || !bc || !ca) {
    cout << -1 << endl;
  } else {
    cout << min(ab + bc, min(bc + ca, ca + ab)) << endl;
  }
  return 0;
}