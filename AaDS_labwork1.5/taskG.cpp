#include <iostream>

using namespace std;


struct Node {
    int key = 0, count = 1, priority = 0;
    Node *left = nullptr, *right = nullptr;

    explicit Node(int key) : key(key), count(1) {
        priority = rand();
        left = right = nullptr;
    }
} *root;


inline int getCount(Node *node) {
    return node == nullptr ? 0 : node->count;
}

inline int leftCount(Node *node) {
    return node == nullptr ? 0 : getCount(node->left);
}

inline void update(Node *node) {
    if (node == nullptr) return;

    node->count = 1;
    if (node->left != nullptr) node->count += node->left->count;
    if (node->right != nullptr) node->count += node->right->count;
}

void split(Node *node, Node *&left, Node *&right, int key) {
    if (node == nullptr) left = right = nullptr;
    else if (leftCount(node) < key) {
        split(node->right, node->right, right, key - (leftCount(node) + 1));
        update(right);
        update(node);
        left = node;
    } else {
        split(node->left, left, node->left, key);
        update(left);
        update(node);
        right = node;
    }
}

Node *merge(Node *left, Node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    } else if (right->priority < left->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

Node *find(Node *node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < leftCount(node)) return find(node->left, key);
    else if (leftCount(node) < key) return find(node->right, key);
    else return node;
}

inline bool exists(int key) {
    return find(root, key) != nullptr;
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        root = merge(root, new Node(i));
    }
}

void print(Node *node) {
    if (node == nullptr) return;
    print(node->left);
    cout << node->key << " ";
    print(node->right);
}


int main() {
    int n, m;
    cin >> n >> m;
    build(n);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        Node *left, *mid, *right;
        left = mid = right = nullptr;
        split(root, left, mid, l - 1);
        split(mid, mid, right, r - l + 1);
        root = merge(mid, merge(left, right));
    }

    print(root);
    return 0;
}