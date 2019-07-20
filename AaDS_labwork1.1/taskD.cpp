#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, tmp;
    char ch;
    cin >> n;
    deque<int> a, b;

    for (int i = 0; i < n; i++) {
        cin >> ch;

        if (ch == '+') {
            cin >> tmp;
            b.push_back(tmp);

            if (a.size() < b.size()) {
                a.push_back(b.front());
                b.pop_front();
            }
        } else if (ch == '*') {
            cin >> tmp;
            a.push_back(tmp);

            if (b.size() + 1 < a.size()) {
                b.push_front(a.back());
                a.pop_back();
            }
        } else {
            cout << a.front() << endl;
            a.pop_front();

            if (a.size() < b.size()) {
                a.push_back(b.front());
                b.pop_front();
            }
        }
    }
    return 0;
}
