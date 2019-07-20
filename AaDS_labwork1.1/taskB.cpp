#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, i, tmp, ans = 0;
    cin >> n;
    stack<pair<int, int>> data;

    for (i = 0; i < n; i++) {
        cin >> tmp;
        if (data.empty() || data.top().first != tmp) {
            data.push({tmp, 1});
        } else {
            data.top().second++;
        }

        if (3 <= data.top().second) {
            i++;
            break;
        }
    }

    for (i; i < n && !data.empty(); i++) {
        cin >> tmp;

        if (data.top().first == tmp) {
            data.top().second++;
        } else {
            if (3 <= data.top().second) {
                ans += data.top().second;
                data.pop();
                if (!data.empty() && data.top().first == tmp) {
                    data.top().second++;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }

    if (!data.empty() && 3 <= data.top().second) {
        ans += data.top().second;
        data.pop();
    }

    cout << ans;
    return 0;
}