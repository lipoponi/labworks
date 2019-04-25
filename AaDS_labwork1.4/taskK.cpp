#include <iostream>

using namespace std;

struct Node {
    int left, right;
    bool taken;
};

int treeSize;
Node *tree;

void build(unsigned int n) {
    treeSize = 1;
    while (treeSize < n) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {
                i, i + 1, true
        };
    }
    for (int i = 0; i < n; i++) {
        tree[treeSize - 1 + i].taken = false;
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = {
                tree[i * 2 + 1].left,
                tree[i * 2 + 2].right,
                tree[i * 2 + 1].taken && tree[i * 2 + 2].taken
        };
    }
}

#ifdef DEBUG
void printTree() {
    cout << "==== tree ====" << endl;
    for (int i = 0; i < treeSize * 2 - 1; i++) {
        printf("[%d; %d) %d\n", tree[i].left, tree[i].right, tree[i].taken);
    }
    cout << endl;
}
#endif

void pop(int node) {
    tree[node].taken = tree[node * 2 + 1].taken && tree[node * 2 + 2].taken;
}

int enter(int node, int &p) {
    int left = tree[node].left;
    int right = tree[node].right;
    int mid = (left + right) / 2;

    if (tree[node].taken) {
        return -1;
    } else if (left == p && p + 1 == right) {
        if (tree[node].taken) return -1;
        else {
            tree[node].taken = true;
            return p;
        }
    } else if (left <= p && p < right) {
        int res;

        if (p < mid) {
            res = enter(node * 2 + 1, p);
            if (res == -1) res = enter(node * 2 + 2, mid);
        } else {
            res = enter(node * 2 + 2, p);
        }

        pop(node);
        return res;
    } else {
        return -1;
    }
}

void exit(int node, int &p) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (left == p && p + 1 == right) {
        tree[node].taken = false;
    } else if (left <= p && p < right) {
        exit(node * 2 + 1, p);
        exit(node * 2 + 2, p);
        pop(node);
    }
}


int main() {
#ifndef DEBUG
    freopen("parking.in", "r+", stdin);
    freopen("parking.out", "w+", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif

    unsigned int n, m;
    cin >> n >> m;
    build(n);

#ifdef DEBUG
    printTree();
#endif

    string command;
    int x;
    for (int i = 0; i < m; i++) {
        cin >> command >> x;
        x--;

        if (command == "enter") {
            int res = enter(0, x);
            if (res == -1) res = enter(0, x = 0);
            cout << res + 1 << endl;
        } else if (command == "exit") {
            exit(0, x);
        }

#ifdef DEBUG
        printTree();
#endif
    }
    return 0;
}