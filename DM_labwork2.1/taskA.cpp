#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

int main() {
#ifndef DEBUG
    freopen("exam.in", "r+", stdin);
    freopen("exam.out", "w+", stdout);
#endif

    int k, n;
    cin >> k >> n;

    unsigned long long sum = 0;
    for (int i = 0; i < k; i++) {
        unsigned long long p, e;
        scanf("%llu %llu", &p, &e);
        sum += p * e;
    }

    cout << fixed;
    cout << setprecision(6) << sum / (double) (n * 100) << endl;
    return 0;
}