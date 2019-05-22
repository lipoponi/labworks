#include <iostream>

using namespace std;

long long *st;
int stSize;

void stSet(int p, long long int value) {
    int position = stSize - 2 + p;
    st[position] = value;
    while (position) {
        position = (position - 1) / 2;
        st[position] = st[position * 2 + 1] + st[position * 2 + 2];
    }
}

long long sum(int position, int cl, int cr, int &l, int &r) {
    int cm = (cl + cr) / 2;
    if (l <= cl && cr <= r) {
        return st[position];
    } else if (r <= cl || cr <= l) {
        return 0;
    } else {
        return sum(position * 2 + 1, cl, cm, l, r) + sum(position * 2 + 2, cm, cr, l, r);
    }
}

long long sum(int l, int r) {
    l--;
    return sum(0, 0, stSize, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    stSize = 1;
    while (stSize < n) stSize *= 2;

    st = new long long[stSize * 2 - 1];
    for (int i = 0; i < stSize * 2 - 1; i++) {
        st[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> st[stSize - 1 + i];
    }
    for (int i = stSize - 2; 0 <= i; i--) {
        st[i] = st[i * 2 + 1] + st[i * 2 + 2];
    }


    string command;
    while (cin >> command) {
        if (command == "set") {
            int i;
            long long x;
            cin >> i >> x;
            stSet(i, x);
        } else if (command == "sum") {
            int i, j;
            cin >> i >> j;
            cout << sum(i, j) << endl;
        }
    }

    return 0;
}