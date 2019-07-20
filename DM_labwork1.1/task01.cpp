#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("allvectors.in", "r+", stdin);
    freopen("allvectors.out", "w+", stdout);

    int n, p;
    cin >> n;
    p = static_cast<int>(pow(2, n));

    for (int i = 0; i < p; i++) {
        string ans;
        int tmp = i;

        for (int j = 0; j < n; j++) {
            ans += tmp % 2 + '0';
            tmp /= 2;
        }

        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
    return 0;
}