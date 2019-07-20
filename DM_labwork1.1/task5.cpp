#include <bits/stdc++.h>

using namespace std;

int n, k;

void doDim(string &buffer, int dim) {
    if (buffer.size() == dim) {
        cout << buffer << endl;
        return;
    }

    bool increasing = buffer[dim] == '0';

    for (int i = 0; i < k; i++) {
        if (increasing) {
            buffer[dim] = static_cast<char>(i + '0');
        } else {
            buffer[dim] = static_cast<char>(k - i - 1 + '0');
        }

        doDim(buffer, dim + 1);
    }
}

int main() {
    freopen("telemetry.in", "r+", stdin);
    freopen("telemetry.out", "w+", stdout);
    cin >> n >> k;

    string buffer;
    for (int i = 0; i < n; i++) {
        buffer += '0';
    }
    doDim(buffer, 0);
    return 0;
}
