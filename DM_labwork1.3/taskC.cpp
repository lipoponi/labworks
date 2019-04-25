#include <iostream>
#include <iomanip>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("lottery.in", "r+", stdin);
    freopen("lottery.out", "w+", stdout);
#endif

    unsigned int n, m;
    cin >> n >> m;

    double p = 1, e = 0;
    unsigned int prev = 0;
    for (int i = 0; i < m; i++) {
        unsigned int a, b;
        cin >> a >> b;

        e += p * prev * (a - 1) / a;
        if (i + 1 == m) e += p * b / a;

        p /= a;
        prev = b;
    }

    cout << fixed;
    cout << setprecision(10) << n - e << endl;
    return 0;
}