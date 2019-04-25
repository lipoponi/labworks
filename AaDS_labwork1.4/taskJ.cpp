#include <iostream>

using namespace std;

struct Node {
    int left, right;
    int min, max;
};

int treeSize;
Node *tree;

#ifdef DEBUG

void printTree() {
    cout << "==== tree ====" << endl;
    for (int i = 0; i < treeSize * 2 - 1; i++) {
        printf("[%d; %d) {%d, %d}\n", tree[i].left, tree[i].right, tree[i].min, tree[i].max);
    }
    cout << endl;
}

#endif

void build(int n) {
    treeSize = 1;
    while (treeSize < n) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {i, i + 1, 0, 0};
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = {tree[i * 2 + 1].left, tree[i * 2 + 2].right, 0, 0};
    }
}

void push(int node) {
    tree[node * 2 + 1].min = max(tree[node].min, tree[node * 2 + 1].min);
    tree[node * 2 + 2].min = max(tree[node].min, tree[node * 2 + 2].min);
    tree[node * 2 + 1].max = max(tree[node].min, tree[node * 2 + 1].max);
    tree[node * 2 + 2].max = max(tree[node].min, tree[node * 2 + 2].max);
}

void pop(int node) {
    tree[node].min = min(tree[node * 2 + 1].min, tree[node * 2 + 2].min);
    tree[node].max = max(tree[node * 2 + 1].max, tree[node * 2 + 2].max);
}

void defend(int node, int a, int b, int x) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        tree[node].min = max(x, tree[node].min);
        tree[node].max = max(x, tree[node].max);
    } else if (right <= a || b <= left) {
        return;
    } else {
        push(node);
        defend(node * 2 + 1, a, b, x);
        defend(node * 2 + 2, a, b, x);
        pop(node);
    }
}

pair<int, int> attack(int node, int a, int b) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        if (left + 1 == right) {
            return {left, tree[node].min};
        } else {
            push(node);
            if (tree[node * 2 + 1].min <= tree[node * 2 + 2].min) {
                return attack(node * 2 + 1, a, b);
            } else {
                return attack(node * 2 + 2, a, b);
            }
        }
    } else if (right <= a || b <= left) {
        return {
                -1, INT32_MAX
        };
    } else {
        push(node);
        pair<int, int> f = attack(node * 2 + 1, a, b);
        pair<int, int> s = attack(node * 2 + 2, a, b);
        pop(node);

        if (f.second <= s.second) {
            return
                    f;
        } else
            return
                    s;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned int n, m;
    cin >> n >> m;

    build(n);

    string command;
    for (int i = 0; i < m; i++) {
        cin >> command;
        if (command == "defend") {
            int a, b, x;
            cin >> a >> b >> x;
            a--;
            defend(0, a, b, x);
        } else {
            int a, b;
            cin >> a >> b;
            a--;
            pair<int, int> result = attack(0, a, b);
            cout << result.second << " " << result.first + 1 << endl;
        }

#ifdef DEBUG
        printTree();
#endif
    }
    return 0;
}