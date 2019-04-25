#include <bits/stdc++.h>

using namespace std;

struct Event {
    int position, value;
    bool add;

    friend bool operator<(Event &a, Event &b) {
        return a.position < b.position;
    }
};

struct Node {
    int left, right, val;
};

int treeSize;
Node *tree;

void build(vector<int> &a) {
    treeSize = 1;
    while (treeSize < a.size()) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {i, i + 1, INT32_MIN};
    }
    for (int i = 0; i < a.size(); i++) {
        tree[treeSize - 1 + i].val = a[i];
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = {
                tree[i * 2 + 1].left,
                tree[i * 2 + 2].right,
                min(tree[i * 2 + 1].val, tree[i * 2 + 2].val)
        };
    }
}

int query(unsigned int node, int &a, int &b) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        return tree[node].val;
    } else if (right <= a || b <= left) {
        return INT32_MAX;
    } else {
        return min(query(node * 2 + 1, a, b), query(node * 2 + 2, a, b));
    }
}

int main() {
#ifndef DEBUG
    freopen("rmq.in", "r+", stdin);
    freopen("rmq.out", "w+", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif

    unsigned int n, m;
    cin >> n >> m;

    vector<int> x(m), l(m), r(m);
    vector<Event> events;
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i] >> x[i];
        l[i]--;
        events.push_back({l[i], x[i], true});
        events.push_back({r[i], x[i], false});
    }

    sort(events.begin(), events.end());

    multiset<int> qs;
    vector<int> result(n, INT32_MIN);
    int p = 0;
    for (int i = 0; i < result.size(); i++) {
        while (events[p].position == i && p < events.size()) {
            if (events[p].add) {
                qs.insert(events[p].value);
            } else {
                qs.erase(qs.find(events[p].value));
            }
            p++;
        }

        if (!qs.empty())
            result[i] = (*qs.rbegin());
    }

    build(result);

    for (int i = 0; i < m; i++) {
        if (x[i] != query(0, l[i], r[i])) {
            cout << "inconsistent" << endl;
            return 0;
        }
    }

    cout << "consistent" << endl;
    for (int &v : result) {
        cout << v << " ";
    }
    return 0;
}