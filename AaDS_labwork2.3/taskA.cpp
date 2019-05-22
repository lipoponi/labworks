#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int v, vector<unordered_set<int>> &tree, vector<vector<int>> &bl, vector<bool> &used) {
    if (used[v]) return;
    used[v] = true;

    for (int i = 1; i < bl[v].size(); i++) {
        if (bl[v][i - 1] == -1) bl[v][i] = -1;
        else bl[v][i] = bl[bl[v][i - 1]][i - 1];
    }

    for (int next : tree[v]) {
        dfs(next, tree, bl, used);
    }
}

int main() {
    int n;
    cin >> n;

    vector<unordered_set<int>> tree(n);
    vector<vector<int>> bl(n, vector<int>(32, -1));

    int root = 0;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        if (v == 0) {
            root = i;
        } else {
            tree[i].insert(v - 1);
            tree[v - 1].insert(i);
            bl[i][0] = v - 1;
        }
    }

    vector<bool> used(n, false);
    dfs(root, tree, bl, used);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";

        for (int lift : bl[i]) {
            if (lift == -1) break;
            cout << lift + 1 << " ";
        }

        cout << endl;
    }
    return 0;
}