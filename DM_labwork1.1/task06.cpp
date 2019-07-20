#include <bits/stdc++.h>

using namespace std;

int fib(int no) {
    int a = 1, b = 1;

    for (int i = 0; i < no; i++) {
        int c = a + b;
        a = b;
        b = c;
    }

    return b;
}

bool check(int a) {
    bool last = a % 2;
    a /= 2;
    while (a) {
        if (a % 2 && last) {
            return false;
        }
        last = a % 2;
        a /= 2;
    }

    return true;
}

int main() {
    freopen("vectors.in", "r+", stdin);
    freopen("vectors.out", "w+", stdout);
    int n, p;
    cin >> n;
    p = static_cast<int>(pow(2, n));

    cout << fib(n) << endl;
    for (int i = 0; i < p; i++) {
        if (check(i)) {
            string ans;
            int h = i;

            for (int j = 0; j < n; j++) {
                ans += h % 2 + '0';
                h /= 2;
            }
            reverse(ans.begin(), ans.end());
            cout << ans << endl;
        }
    }
    return 0;
}