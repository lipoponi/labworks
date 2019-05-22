#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int left, right;
    long long val, add, set;
    bool real, isSet;
};

int treeSize;
Node *tree;

Node opMin(Node a, Node b) {
    Node result = {};
    result.real = a.real || b.real;

    if (a.real && b.real) {
        result.val = min(a.val, b.val);
    } else if (a.real) {
        result.val = a.val;
    } else if (b.real) {
        result.val = b.val;
    } else {
        result.val = 0;
    }

    return result;
}

void build(const long long *a, int aSize) {
    treeSize = 1;
    while (treeSize < aSize) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize * 2 - 1; i++) tree[i] = {0, 0, 0, 0, false, false};
    for (int i = 0; i < aSize; i++) {
        tree[treeSize - 1 + i].val = a[i];
        tree[treeSize - 1 + i].real = true;
    }
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i].left = i;
        tree[treeSize - 1 + i].right = i + 1;
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = opMin(tree[i * 2 + 1], tree[i * 2 + 2]);
        tree[i].left = tree[i * 2 + 1].left;
        tree[i].right = tree[i * 2 + 2].right;
    }
}

void push(int node) {
    if (tree[node].isSet) {
        tree[node].isSet = false;
        tree[node * 2 + 1].isSet = tree[node * 2 + 2].isSet = true;
        tree[node * 2 + 1].val = tree[node * 2 + 2].val = tree[node].set;
        tree[node * 2 + 1].set = tree[node * 2 + 2].set = tree[node].set;
        tree[node * 2 + 1].add = tree[node * 2 + 2].add = 0;
    }
    tree[node * 2 + 1].add += tree[node].add;
    tree[node * 2 + 2].add += tree[node].add;
    tree[node * 2 + 1].val += tree[node].add;
    tree[node * 2 + 2].val += tree[node].add;
    tree[node].add = 0;
}

void updateSet(int node, int a, int b, long long x) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        tree[node].set = tree[node].val = x;
        tree[node].isSet = true;
        tree[node].add = 0;
    } else if (right <= a || b <= left) {
        return;
    } else {
        push(node);
        updateSet(node * 2 + 1, a, b, x);
        updateSet(node * 2 + 2, a, b, x);
        tree[node].val = min(tree[node * 2 + 1].val, tree[node * 2 + 2].val);
    }
}

void updateAdd(int node, int a, int b, long long x) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        tree[node].add += x;
        tree[node].val += x;
    } else if (right <= a || b <= left) {
        return;
    } else {
        push(node);
        updateAdd(node * 2 + 1, a, b, x);
        updateAdd(node * 2 + 2, a, b, x);
        tree[node].val = min(tree[node * 2 + 1].val, tree[node * 2 + 2].val);
    }
}

long long queryMin(int node, int a, int b) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        return tree[node].val;
    } else if (right <= a || b <= left) {
        return 0;
    } else {
        push(node);

        vector<long long> pool;
        int mid = (left + right) / 2;
        if (!(b <= left || mid <= a)) pool.push_back(queryMin(node * 2 + 1, a, b));
        if (!(b <= mid || right <= a)) pool.push_back(queryMin(node * 2 + 2, a, b));

        return (*min_element(pool.begin(), pool.end()));
    }
}

int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif

    int n;
    cin >> n;
    auto *a = new long long[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(a, n);
#ifdef DEBUG
    for (int i = 0; i < treeSize * 2 - 1; i++) {
        printf("%d %lld: (%d %d) {%d %lld}\n", tree[i].real, tree[i].val, tree[i].left, tree[i].right, tree[i].isSet,
               tree[i].add);
    }
#endif

    string command;
    while (cin >> command) {
        if (command == "set") {
            int i, j;
            long long x;
            cin >> i >> j >> x;
            i--;

            updateSet(0, i, j, x);
        } else if (command == "add") {
            int i, j;
            long long x;
            cin >> i >> j >> x;
            i--;

            updateAdd(0, i, j, x);
        } else if (command == "min") {
            int i, j;
            cin >> i >> j;
            i--;

            cout << queryMin(0, i, j) << endl;
        }
#ifdef DEBUG
        for (int i = 0; i < treeSize * 2 - 1; i++) {
            printf("%d %lld: (%d %d) {%d %lld}\n", tree[i].real, tree[i].val, tree[i].left, tree[i].right,
                    tree[i].isSet, tree[i].add);
        }
#endif
    }

    return 0;
}