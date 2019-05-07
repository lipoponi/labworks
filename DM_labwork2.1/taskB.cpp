#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("shooter.in", "r+", stdin);
    freopen("shooter.out", "w+", stdout);
#endif

    int n, m, k;
    cin >> n >> m >> k;

    double o = 0, q = 0;
    for (int i = 1; i <= n; i++) {
        double p;
        cin >> p;
        p = pow(1 - p, m);
        q += p;
        if (i == k) o = p;
    }

    cout << fixed;
    cout << setprecision(14) << o / q << endl;
    return 0;
}