#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, tmp, lastout = -1;
    cin>>n;
    stack<int> s;
    vector<bool> ans;

    for (int i = 0; i < n; i++) {
        scanf("%d", &tmp);

        while (!s.empty() && s.top() < tmp) {
            if (s.top() < lastout) {
                cout << "impossible" << endl;
                return 0;
            }
            lastout = s.top();
            s.pop();
            ans.push_back(false);
        }

        s.push(tmp);
        ans.push_back(true);
    }

    while (!s.empty()) {
        if (s.top() < lastout) {
            cout << "impossible" << endl;
            return 0;
        }
        lastout = s.top();
        s.pop();
        ans.push_back(false);
    }

    for (bool push : ans) {
        if (push) {
            printf("push\n");
        } else {
            printf("pop\n");
        }
    }
    return 0;
}