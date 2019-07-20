#include <bits/stdc++.h>

using namespace std;

template<typename T>
class astroQ {
private:
    unordered_map<T, int> id_ticket;
    deque<pair<T, int>> people;
    int lastTicket = 1;
public:
    void push(T id) {
        id_ticket[id] = lastTicket;
        people.push_back({id, lastTicket++});
    }

    void popFront() {
        people.pop_front();
    }

    void popBack() {
        lastTicket--;
        people.pop_back();
    }

    int howManyBefore(T id) {
        return id_ticket[id] - people.front().second;
    }

    T frontId() {
        return people.front().first;
    }
};

int main() {
    int n, cmd, tmp;
    cin >> n;
    astroQ<int> q;

    for (int i = 0; i < n; i++) {
        scanf("%d", &cmd);

        switch (cmd) {
            case 1:
                scanf("%d", &tmp);
                q.push(tmp);
                break;
            case 2:
                q.popFront();
                break;
            case 3:
                q.popBack();
                break;
            case 4:
                scanf("%d", &tmp);
                printf("%d\n", q.howManyBefore(tmp));
                break;
            case 5:
                printf("%d\n", q.frontId());
                break;
            default:
                break;
        }
    }
    return 0;
}