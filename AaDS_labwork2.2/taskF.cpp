#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key = 0, count = 1, priority = 0;
    Node *left = nullptr, *right = nullptr;

    explicit Node(int key) : key(key), count(1) {
        priority = rand();
        left = right = nullptr;
    }
} *root;


inline void upd(Node *node) {
    if (node == nullptr) return;

    node->count = 1;
    if (node->left != nullptr) node->count += node->left->count;
    if (node->right != nullptr) node->count += node->right->count;
}

void split(Node *node, Node *&left, Node *&right, int key) {
    if (node == nullptr) left = right = nullptr;
    else if (node->key < key) {
        split(node->right, node->right, right, key);
        upd(right);
        upd(node);
        left = node;
    } else {
        split(node->left, left, node->left, key);
        upd(left);
        upd(node);
        right = node;
    }
}

Node *merge(Node *left, Node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    } else if (right->priority < left->priority) {
        left->right = merge(left->right, right);
        upd(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        upd(right);
        return right;
    }
}

Node *find(Node *node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < node->key) return find(node->left, key);
    else if (node->key < key) return find(node->right, key);
    else return node;
}

inline bool exists(int key) {
    return find(root, key) != nullptr;
}

void insert(int key) {
    if (exists(key)) return;
    Node *left, *right;
    left = right = nullptr;
    split(root, left, right, key);
    root = merge(merge(left, new Node(key)), right);
}

void remove(Node *&node, int key) {
    if (node == nullptr) return;

    if (key < node->key) remove(node->left, key);
    else if (node->key < key) remove(node->right, key);
    else node = merge(node->left, node->right);

    upd(node);
}

inline int getCount(Node *node) {
    return node == nullptr ? 0 : node->count;
}

Node *query(Node *node, int k) {
    if (node == nullptr) return nullptr;

    if (k <= getCount(node->right)) return query(node->right, k);
    if (k == getCount(node->right) + 1) return node;
    if (getCount(node->right) + 1 < k) return query(node->left, k - (getCount(node->right) + 1));

    return nullptr;
}


int main() {
    unsigned int n;
    cin >> n;
    srand(n);

    for (int i = 0; i < n; i++) {
        int c, k;
        cin >> c >> k;

        switch (c) {
            case +1:
                insert(k);
                break;
            case 0:
                cout << query(root, k)->key << endl;
                break;
            case -1:
                remove(root, k);
                break;
            default:
                break;
        }
    }
    return 0;
}