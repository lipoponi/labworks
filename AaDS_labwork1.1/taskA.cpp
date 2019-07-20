#include <bits/stdc++.h>

using namespace std;

template<typename T>
class stuck {
private:
    stack<T> data, minimal;
public:
    inline void push(T value) {
        data.push(value);
        if (minimal.empty() || value < this->minimal.top()) {
            this->minimal.push(value);
        } else {
            this->minimal.push(this->minimal.top());
        }
    }

    inline void pop() {
        data.pop();
        minimal.pop();
    }

    inline T min() {
        return minimal.top();
    }
};

int main() {
    int n, tmp, cmd;
    cin >> n;
    stuck<int> data;

    for (int i = 0; i < n; i++) {
        scanf("%d", &cmd);

        switch (cmd) {
            case 1:
                scanf("%d", &tmp);
                data.push(tmp);
                break;
            case 2:
                data.pop();
                break;
            case 3:
                printf("%d\n", data.min());
                break;
            default:
                break;
        }
    }
    return 0;
}