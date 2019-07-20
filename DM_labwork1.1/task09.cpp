#include <bits/stdc++.h>

using namespace std;

int n;

void doGen(string buffer, int balance) {
    if (balance < 0) {
        return;
    }

    if (n*2 <= buffer.length()) {
        if (balance == 0) {
            cout << buffer << endl;
        }

        return;
    }

    doGen(buffer + '(', balance + 1);
    doGen(buffer + ')', balance - 1);
}

int main() {
    freopen("brackets.in", "r+", stdin);
    freopen("brackets.out", "w+", stdout);
    cin >> n;

    doGen(string(), 0);
    return 0;
}