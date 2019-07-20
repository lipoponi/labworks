#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("chaincode.in", "r+", stdin);
    freopen("chaincode.out", "w+", stdout);
    int n;
    cin >> n;

    set<string> has;
    string buffer;
    for (int i = 0; i < n; i++) {
        buffer += '0';
    }

    while (true) {
        has.insert(buffer);
        cout << buffer << endl;
        buffer.erase(buffer.begin());
        if (has.find(buffer + '1') == has.end()) {
            buffer += '1';
        } else if (has.find(buffer + '0') == has.end()) {
            buffer += '0';
        } else {
            break;
        }
    }
    return 0;
}