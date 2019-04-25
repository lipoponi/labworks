#include <bits/stdc++.h>

using namespace std;

#ifndef DEBUG
const int esize = 500000;
const int offset = 200002;
#else
const int esize = 5;
const int offset = 0;
#endif

struct Event {
    int pos, xl, xr;
    bool start;

    Event(int pos, int xl, int xr, bool start) {
        this->pos = pos;
        this->xl = xl;
        this->xr = xr;
        this->start = start;
    }

    friend bool operator<(Event &a, Event &b) {
        return a.pos < b.pos;
    }
};

struct Node {
    int left, right;
    int max, d;
};

int treeSize;
Node *tree;

void build(int n) {
    treeSize = 1;
    while (treeSize < n) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {
                i, i + 1,
                0, 0
        };
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = {
                tree[i * 2 + 1].left,
                tree[i * 2 + 2].right,
                0, 0
        };
    }
}

void printTree() {
    cout << "==== tree ====" << endl;
    for (int i = 0; i < treeSize * 2 - 1; i++) {
        printf("[%d; %d) %d %d\n", tree[i].left, tree[i].right, tree[i].max, tree[i].d);
    }
    cout << endl;
}

void push(int node) {
    tree[2 * node + 1].d = tree[2 * node + 1].d + tree[node].d;
    tree[2 * node + 2].d = tree[2 * node + 2].d + tree[node].d;
    tree[node].d = 0;
}

void update(int node, int a, int b, int val) {
    int l = tree[node].left;
    int r = tree[node].right;
    if (r <= a || b <= l)
        return;
    if (a <= l && r <= b) {
        tree[node].d = tree[node].d + val;
        return;
    }

    push(node);
    update(2 * node + 1, a, b, val);
    update(2 * node + 2, a, b, val);
    tree[node].max = max((tree[2 * node + 1].max + tree[2 * node + 1].d),
                         (tree[2 * node + 2].max + tree[2 * node + 2].d));
}

pair<int, int> query(int node, int a, int b) {
    int l = tree[node].left;
    int r = tree[node].right;
    if (r <= a || b <= l)
        return {0, 0};
    if (a <= l && r <= b)
        return {tree[node].max + tree[node].d, l};

    push(node);
    pair<int, int> o, p;
    o = query(node * 2 + 1, a, b);
    p = query(node * 2 + 2, a, b);

    pair<int, int> ans;
    if (o.first < p.second) {
        ans = p;
    } else {
        ans = o;
    }


    tree[node].max = max((tree[2 * node + 1].max + tree[2 * node + 1].d),
                         (tree[2 * node + 2].max + tree[2 * node + 2].d));
    return ans;
}

int main() {
    int n;
    cin >> n;
    build(esize);
#ifdef DEBUG
    printTree();
#endif

    vector<Event> e;
    int ry, rx, rm = 1;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x2++;
        y2++;
        x1 += offset;
        y1 += offset;
        x2 += offset;
        y2 += offset;
        ry = y1;
        rx = x1;

        e.emplace_back(Event(y1, x1, x2, true));
        e.emplace_back(Event(y2, x1, x2, false));
    }

    sort(e.begin(), e.end());

    int p = 0;
    while (p < e.size()) {
        int last = e[p].pos;
        while (last == e[p].pos) {
            update(0, e[p].xl, e[p].xr, e[p].start ? 1 : -1);
#ifdef DEBUG
            printTree();
#endif
            p++;
        }

        pair<int, int> result = query(0, 0, treeSize);

        if (rm < result.first) {
            rm = result.first;
            rx = result.second;
            ry = last;
        }
    }

    rx -= offset;
    ry -= offset;

    cout << rm << endl << rx + 1 << " " << ry << endl;
    return 0;
}