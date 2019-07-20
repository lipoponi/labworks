#include <bits/stdc++.h>

using namespace std;

int main() {
    stack<int> buffer;
    char tmp;

    while (cin >> tmp) {
        if ('0' <= tmp && tmp <= '9') {
            buffer.push(tmp - '0');
        } else {
            int a = buffer.top();
            buffer.pop();
            int b = buffer.top();
            buffer.pop();

            switch (tmp) {
                case '+':
                    buffer.push(a + b);
                    break;
                case '-':
                    buffer.push(b - a);
                    break;
                case '*':
                    buffer.push(a * b);
                    break;
                default:
                    break;
            }
        }
    }

    cout << buffer.top();
    return 0;
}