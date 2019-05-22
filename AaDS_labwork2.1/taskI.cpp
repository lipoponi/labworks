#include <bits/stdc++.h>

using namespace std;

struct Node {
    int lb, rb;
    int diff, max;
    Node *l, *r;

    Node(int left, int right) {
        lb = left;
        rb = right;
        l = r = nullptr;
        diff = max = 0;
    }

    ~Node() {
        reduce();
    }

    void reduce() {
        if (l != nullptr) delete l;
        if (r != nullptr) delete r;
        l = r = nullptr;
    }

    bool childFree() {
        return l == nullptr && r == nullptr;
    }
} *root;

void build(long long n) {
    long long treeSize = 1;
    while (treeSize < n) treeSize *= 2;

    root = new Node(0, treeSize);
}

void printTree(Node *node, long long depth = 0) {
#ifdef DEBUG
    if (node == nullptr) return;

    printTree(node->l, depth + 1);

    for (int i = 0; i < depth; i++) cout << " ";
    printf("%d [%lld; %lld) %lld %lld\n", node->childFree(), node->lb, node->rb, node->diff, node->max);

    printTree(node->r, depth + 1);
#endif
}


void push(Node *node) {
    if (node->childFree()) {
        node->l = new Node(node->lb, (node->lb + node->rb) / 2);
        node->r = new Node((node->lb + node->rb) / 2, node->rb);
        node->l->diff = node->r->diff = node->diff / 2;
        node->l->max = node->r->max = node->max / 2;
    }
}

void pop(Node *node) {
    node->max = max(node->l->max, node->l->diff + node->r->max);
    node->diff = node->l->diff + node->r->diff;
}


void update(Node *node, long long a, long long b, long long D) {
    long long left = node->lb;
    long long right = node->rb;

    if (a <= left && right <= b) {
        node->diff = (right - left) * D;
        node->max = max(0LL, (right - left) * D);
        node->reduce();
    } else if (right <= a || b <= left) {
        return;
    } else {
        push(node);
        update(node->l, a, b, D);
        update(node->r, a, b, D);
        pop(node);
    }
}

long long query(Node *node, long long h) {
    long long left = node->lb;
    long long right = node->rb;

    if (node->max <= h) {
        return right - left;
    } else if (left + 1 != right) {
        push(node);
        if (node->l->max <= h) {
            return (right - left) / 2 + query(node->r, h - node->l->diff);
        } else {
            return query(node->l, h);
        }
    } else {
        return 0;
    }
}


int main() {
    long long n;
    cin >> n;

    build(n);

    while (true) {
        char c;
        cin >> c;

        if (c == 'Q') {
            long long h;
            cin >> h;
            cout << min(query(root, h), n) << endl;
        } else if (c == 'I') {
            long long a, b, D;
            cin >> a >> b >> D;
            a--;
            update(root, a, b, D);
        } else break;

        printTree(root);
    }
    return 0;
}