#include <iostream>

using namespace std;

int main() {
    uint_fast64_t n, x, y, a0;
    cin >> n >> x >> y >> a0;
    int_fast64_t m, z, t, b0;
    cin >> m >> z >> t >> b0;

    uint_fast16_t ca = a0;
    auto *presum = new unsigned long long[n];
    presum[0] = ca;
    for (int i = 1; i < n; i++) {
        ca = (x * ca + y);
        presum[i] = ca + presum[i - 1];
    }

#ifdef DEBUG
    cout << "========" << endl;
    for (int i = 0; i < n; i++) {
        cout << presum[i] << " ";
    }
    cout << endl;
#endif

    uint_fast32_t modulus = 1024 * 1024 * 1024, cb = (uint_fast32_t) b0;
    uint_fast64_t sum = 0;

    for (int i = 0; i < m; i++) {
        uint_fast32_t c1, c2;
        c1 = (cb+n) % n;
        cb = uint_fast32_t((z * cb + t + modulus) % modulus);
        c2 = (cb+n) % n;
        cb = uint_fast32_t((z * cb + t + modulus) % modulus);

        uint_fast32_t mn = min(c1, c2), mx = max(c1, c2);
        sum += presum[mx];
        if (mn != 0) sum -= presum[mn - 1];
    }

    cout << sum;
    return 0;
}