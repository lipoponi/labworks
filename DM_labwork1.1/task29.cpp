#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("nextpartition.in", "r+", stdin);
    freopen("nextpartition.out", "w+", stdout);
    int n;
    char c;
    cin >> n;
    vector<int> v;
    while (cin >> c) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    if (v.size() == 1) {
        cout << "No solution" << endl;
        return 0;
    }

    v[v.size() - 1]--;
    v[v.size() - 2]++;
    if (v[v.size() - 2] > v[v.size() - 1]) {
        v[v.size() - 2] += v[v.size() - 1];
        v.pop_back();
    } else {
        while (v[v.size() - 2] * 2 <= v[v.size() - 1]) {
            v.push_back(v[v.size() - 1] - v[v.size() - 2]);
            v[v.size() - 2] = v[v.size() - 3];
        }
    }

    cout << n << "=" << v[0];
    for (int i = 1; i < v.size(); i++) {
        cout << "+" << v[i];
    }
    return 0;
}

/*
 1 2 3
 1 5
 */