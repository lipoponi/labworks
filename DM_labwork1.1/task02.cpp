#include <bits/stdc++.h>

using namespace std;

void doDos(int length, string prefix, bool reverse) {
    if (length == 0) {
        cout << prefix << endl;
        return;
    }

    bool c = reverse;
    doDos(length - 1, prefix + static_cast<char>(c + '0'), false);
    c = !c;
    doDos(length - 1, prefix + static_cast<char>(c + '0'), true);
}

int main() {
    freopen("gray.in", "r+", stdin);
    freopen("gray.out", "w+", stdout);
    int n;
    cin >> n;

    doDos(n - 1, string("0"), false);
    doDos(n - 1, string("1"), true);
    return 0;
}