#include <iostream>

using namespace std;


struct Node {
    Node *left, *right, *parent;
    unsigned int height;
    int key;

    explicit Node(int key, Node *parent) : key(key), parent(parent) {
        height = 1;
        left = right = nullptr;
    }

    ~Node() {
        left = right = parent = nullptr;
    }
} *root;


inline unsigned int getHeight(Node *node) {
    if (node == nullptr) return 0;
    else return node->height;
}

inline void updateHeight(Node *node) {
    if (node == nullptr) return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

inline void updateParent(Node *node) {
    if (node == nullptr) return;
    if (node->left != nullptr) node->left->parent = node;
    if (node->right != nullptr) node->right->parent = node;
}

inline bool isLeftChild(Node *node) {
    if (node == nullptr || node->parent == nullptr) return false;
    return node->parent->left == node;
}

inline bool isRightChild(Node *node) {
    if (node == nullptr || node->parent == nullptr) return false;
    return node->parent->right == node;
}

inline void hangUp(Node *what, Node *toWhat, bool left) {
    if (toWhat != nullptr) {
        if (left) toWhat->left = what;
        else toWhat->right = what;
    }

    if (what != nullptr) {
        what->parent = toWhat;
    }

    updateParent(toWhat);
    updateHeight(toWhat);
}

void doBalance(Node *node) {
    if (getHeight(node->left) + 2 <= getHeight(node->right)) {
        Node *a = node;
        Node *b = node->right;

        if (getHeight(b->left) <= getHeight(b->right)) {
            if (a == root) {
                root = b;
                root->parent = nullptr;
            } else {
                hangUp(b, a->parent, isLeftChild(a));
            }

            Node *C = b->left;
            hangUp(C, a, false);
            hangUp(a, b, true);
        } else {
            Node *c = b->left;
            Node *M = c->left;
            Node *N = c->right;

            if (a == root) {
                root = c;
                root->parent = nullptr;
            } else {
                hangUp(c, a->parent, isLeftChild(a));
            }

            hangUp(M, a, false);
            hangUp(a, c, true);
            hangUp(N, b, true);
            hangUp(b, c, false);
        }
    }

    if (getHeight(node->right) + 2 <= getHeight(node->left)) {
        Node *a = node;
        Node *b = node->left;

        if (getHeight(b->right) <= getHeight(b->left)) {
            if (a == root) {
                root = b;
                root->parent = nullptr;
            } else {
                hangUp(b, a->parent, isLeftChild(a));
            }

            Node *C = b->right;
            hangUp(C, a, true);
            hangUp(a, b, false);
        } else {
            Node *c = b->right;
            Node *M = c->left;
            Node *N = c->right;

            if (a == root) {
                root = c;
                root->parent = nullptr;
            } else {
                hangUp(c, a->parent, isLeftChild(a));
            }

            hangUp(N, a, true);
            hangUp(a, c, false);
            hangUp(M, b, false);
            hangUp(b, c, true);
        }
    }
}


Node *find(Node *node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < node->key) return find(node->left, key);
    else if (node->key < key) return find(node->right, key);
    else return node;
}

Node *next(Node *node, int key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        Node *result = next(node->left, key);
        return result == nullptr ? node : result;
    } else return next(node->right, key);
}

Node *prev(Node *node, int key) {
    if (node == nullptr) return nullptr;

    if (node->key < key) {
        Node *result = prev(node->right, key);
        return result == nullptr ? node : result;
    } else return prev(node->left, key);
}

Node *insert(Node *&node, int key) {
    Node *result = nullptr;

    if (node == nullptr) result = node = new Node(key, nullptr);
    else if (key < node->key) result = insert(node->left, key);
    else if (node->key < key) result = insert(node->right, key);

    updateParent(node);
    updateHeight(node);
    doBalance(node);
    return result;
}

void remove(Node *node) {
    if (node == nullptr) return;
    else if (node->left == nullptr && node->right == nullptr) {
        if (isLeftChild(node)) node->parent->left = nullptr;
        if (isRightChild(node)) node->parent->right = nullptr;
        Node *p = node->parent;
        if (node == root) root = nullptr;
        delete node;

        while (p != nullptr) {
            updateParent(p);
            updateHeight(p);
            doBalance(p);
            p = p->parent;
        }
    } else if (getHeight(node->left) < getHeight(node->right)) {
        Node *p = next(root, node->key);
        node->key = p->key;
        remove(p);
    } else {
        Node *p = prev(root, node->key);
        node->key = p->key;
        remove(p);
    }
}


int main() {
    string command;
    int arg;

    while (cin >> command >> arg) {
        if (command == "insert") insert(root, arg);
        else if (command == "delete") remove(find(root, arg));
        else if (command == "exists") cout << (find(root, arg) == nullptr ? "false" : "true") << endl;
        else if (command == "next") {
            Node *result = next(root, arg);
            if (result == nullptr) cout << "none" << endl;
            else cout << result->key << endl;
        } else if (command == "prev") {
            Node *result = prev(root, arg);
            if (result == nullptr) cout << "none" << endl;
            else cout << result->key << endl;
        }
    }
    return 0;
}