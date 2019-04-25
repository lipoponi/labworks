#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> ST;

void build(const int *a, unsigned int n) {
    auto K = (unsigned int) log2(n) + 1;
    ST.resize(K);
    ST[0].resize(n);
    for (int i = 0; i < n; i++) {
        ST[0][i] = a[i];
    }

    for (int k = 1; k < ST.size(); k++) {
        ST[k].resize(ST[k - 1].size() - (1 << (k - 1)));
        for (int i = 0; i < ST[k].size(); i++) {
            ST[k][i] = min(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]);
        }
    }
}

int query(int l, int r) {
    int k = (int) log2(r - l);
    return min(ST[k][l], ST[k][r - (1 << k)]);
}

int main() {
    int n, m, ca;
    cin >> n >> m >> ca;

    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = ca;
        ca = (23 * ca + 21563) % 16714589;
    }
#ifdef DEBUG
    cout << "==== a ====" << endl;
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << "====" << endl;
#endif

    build(a, n);

#ifdef DEBUG
    cout << "==== ST ====" << endl;
    for (auto &i : ST) {
        for (auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "====" << endl;
#endif

    int cu, cv, cans;
    cin >> cu >> cv;
    int mn = min(cu, cv) - 1, mx = max(cu, cv);
    cans = query(mn, mx);
#ifdef DEBUG
    printf("[%d %d] [%d; %d) -> %d\n", cu, cv, mn, mx, cans);
#endif
    for (int i = 1; i < m; i++) {
        cu = ((17 * cu + 751 + cans + 2 * i) % n) + 1;
        cv = ((13 * cv + 593 + cans + 5 * i) % n) + 1;
        int mn = min(cu, cv) - 1, mx = max(cu, cv);
        cans = query(mn, mx);
#ifdef DEBUG
        printf("[%d %d] [%d; %d) -> %d\n", cu, cv, mn, mx, cans);
#endif
    }

    cout << cu << " " << cv << " " << cans << endl;
    return 0;
}