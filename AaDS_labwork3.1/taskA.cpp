#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<int> deg;
vector<vector<int>> graph;
vector<bool> used;
vector<bool> pushed;
vector<int> result;
bool noSort = false;

void dfs(int v) {
    if (used[v] && !pushed[v]) {
        noSort = true;
    }

    if (used[v]) return;
    used[v] = true;

    for (int next : graph[v]) {
        dfs(next);
    }

    result.push_back(v);
    pushed[v] = true;
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n);
    deg.assign(n, 0);
    used.assign(n, false);
    pushed.assign(n, false);

    for (int i = 0; i < m; i++) {
        int s, d;
        cin >> s >> d;
        s--;
        d--;

        graph[s].push_back(d);
        deg[d]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            dfs(i);
        }
    }

    if (noSort || result.size() != n) {
        cout << -1;
        return 0;
    }

    reverse(result.begin(), result.end());

    for (int v : result) {
        cout << v + 1 << " ";
    }
    return 0;
}