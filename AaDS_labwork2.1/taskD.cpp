#include <iostream>
#include <cmath>

using namespace std;

#ifdef DEBUG
const int MAXLN = 8;
#else
const int MAXLN = 1000000;
#endif

struct Node {
    int left, right;
    int count, length;
    bool leftest, rightest;
    int color;
};

int treeSize;
Node *tree;

void build() {
    treeSize = 1;
    while (treeSize < MAXLN) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {i, i + 1, 0, 0, false, false, 0};
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        Node l = tree[i * 2 + 1], r = tree[i * 2 + 2];
        tree[i] = {l.left, r.right, 0, 0, false, false, 0};
    }
}

void simplify(int node) {
    switch (tree[node].color) {
        case 0:
            tree[node] = {tree[node].left, tree[node].right, 0, 0, false, false, 0};
            break;
        case 1:
            tree[node] = {tree[node].left, tree[node].right, 1, tree[node].right - tree[node].left, true, true, 1};
            break;
    }
}

void push(int node) {
    simplify(node);

    if (tree[node].color < 2) {
        tree[node * 2 + 1].color = tree[node * 2 + 2].color = tree[node].color;
        simplify(node * 2 + 1);
        simplify(node * 2 + 2);
    }
}

void pop(int node) {
    Node l = tree[node * 2 + 1], r = tree[node * 2 + 2];

    tree[node].count = l.count + r.count - (l.rightest && r.leftest);
    tree[node].length = l.length + r.length;
    tree[node].leftest = l.leftest;
    tree[node].rightest = r.rightest;
    tree[node].color = (l.color == r.color ? l.color : 2);
}

void update(int node, int a, int b, bool black) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        tree[node].count = black;
        tree[node].length = black * (right - left);
        tree[node].leftest = black;
        tree[node].rightest = black;
        tree[node].color = black ? 1 : 0;
    } else if (right <= a || b <= left) {
        return;
    } else {
        push(node);
        update(node * 2 + 1, a, b, black);
        update(node * 2 + 2, a, b, black);
        pop(node);
    }
}


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    build();
    int n;
    cin >> n;
    char c;
    int x, l;

    for (int i = 0; i < n; i++) {
        cin >> c >> x >> l;
        x += 500000;
        update(0, x, x + l, c == 'B');
        simplify(0);
        cout << tree[0].count << " " << tree[0].length << endl;
#ifdef DEBUG
        for (int j = 0; j < treeSize * 2 - 1; j++) {
            printf("[%d; %d) %d/%d (%d - %d) %d\n",
                   tree[j].left, tree[j].right,
                   tree[j].length, tree[j].count,
                   tree[j].leftest, tree[j].rightest,
                   tree[j].color
            );
        }
#endif
    }
    return 0;
}