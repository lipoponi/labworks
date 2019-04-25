#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key = 0, priority = 0;
    long long sum = 0;
    Node *left = nullptr, *right = nullptr;

    explicit Node(int key) : key(key), sum(key) {
        priority = rand();
        left = right = nullptr;
    }
} *root;


inline void upd(Node *node) {
    if (node == nullptr) return;

    node->sum = node->key;
    if (node->left != nullptr) node->sum += node->left->sum;
    if (node->right != nullptr) node->sum += node->right->sum;
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

long long query(int l, int r) {
    if (r < l) return 0;
    Node *left, *mid, *right;
    left = mid = right = nullptr;
    split(root, left, mid, l);
    split(mid, mid, right, r + 1);
    long long result = 0;
    if (mid != nullptr) result = mid->sum;
    root = merge(merge(left, mid), right);
    return result;
}


int main() {
    unsigned int n;
    srand(n);
    cin >> n;
    long long lastAns = 0;
    char lastOp = '\0';

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        if (c == '+') {
            int x;
            cin >> x;
            if (lastOp == '?') x = (int) ((x + lastAns) % 1000000000);
            insert(x);
        } else if (c == '?') {
            int l, r;
            cin >> l >> r;
            lastAns = query(l, r);
            cout << lastAns << endl;
        }

        lastOp = c;
    }
    return 0;
}