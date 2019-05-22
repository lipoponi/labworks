#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


struct Treap {
    int count = 1, priority;
    Treap *parent, *left, *right;
    bool cyclic = false;

    Treap() {
        priority = ((rand() << 16) | rand());
        parent = left = right = nullptr;
    }
};


inline int getCount(Treap *node) {
    if (node == nullptr) return 0;
    else return node->count;
}

inline int getKey(Treap *node) {
    if (node == nullptr) return -1;

    int ans = getCount(node->left);
    Treap *last = node;
    node = node->parent;

    while (node != nullptr) {
        if (node->left != last) {
            ans += getCount(node->left) + 1;
        }

        last = node;
        node = node->parent;
    }

    return ans;
}

inline Treap *getRoot(Treap *node) {
    if (node == nullptr) return nullptr;

    while (node->parent != nullptr) {
        node = node->parent;
    }

    return node;
}

inline void update(Treap *node) {
    if (node != nullptr) {
        node->count = 1 + getCount(node->left) + getCount(node->right);

        if (node->parent != nullptr) {
            if (node->parent->left != node && node->parent->right != node) {
                node->parent = nullptr;
            }
        }

        if (node->left != nullptr) node->left->parent = node;
        if (node->right != nullptr) node->right->parent = node;
    }
}


void split(Treap *root, Treap *&left, Treap *&right, int key) {
    if (root == nullptr) left = right = nullptr;
    else if (getCount(root->left) < key) {
        key -= 1 + getCount(root->left);
        split(root->right, root->right, right, key);
        left = root;
    } else {
        split(root->left, left, root->left, key);
        right = root;
    }

    update(left);
    update(right);
}

Treap *merge(Treap *left, Treap *right) {
    if (left == nullptr || right == nullptr) {
        return left == nullptr ? right : left;
    } else if (left->priority < right->priority) {
        right->left = merge(left, right->left);
        update(left);
        update(right->left);
        update(right);
        return right;
    } else {
        left->right = merge(left->right, right);
        update(right);
        update(left->right);
        update(left);
        return left;
    }
}

void reverse(Treap *root) {
    if (root == nullptr) return;

    swap(root->left, root->right);
    reverse(root->left);
    reverse(root->right);
}

void toVector(Treap *root, vector<Treap *> &a) {
    if (root == nullptr) return;

    toVector(root->left, a);
    a.push_back(root);
    toVector(root->right, a);
}


void join(Treap *a, Treap *b) {
    if (a == b) return;

    if (getRoot(a) == getRoot(b)) {
        getRoot(a)->cyclic = true;
    } else {
        if (getKey(a) == 0) reverse(getRoot(a));
        if (getKey(b) != 0) reverse(getRoot(b));
        merge(getRoot(a), getRoot(b));
    }
}

void divide(Treap *a, Treap *b) {
    if (getRoot(a) != getRoot(b) || a == b) return;

    if (getRoot(a)->cyclic) {
        vector<Treap *> disordered;
        toVector(getRoot(a), disordered);

        int aPos = -1, bPos = -1;
        for (int i = 0; i < disordered.size(); i++) {
            (*disordered[i]) = Treap();
            if (disordered[i] == a) aPos = i;
            if (disordered[i] == b) bPos = i;
        }
        if (bPos < aPos) swap(aPos, bPos);

        if (aPos == 0 && bPos == disordered.size() - 1) {
            for (int i = 1; i < disordered.size(); i++) merge(getRoot(disordered[i - 1]), disordered[i]);
        } else {
            vector<Treap *> ordered;
            for (int i = bPos; i < disordered.size(); i++) ordered.push_back(disordered[i]);
            for (int i = 0; i <= aPos; i++) ordered.push_back(disordered[i]);
            for (int i = 1; i < ordered.size(); i++) merge(getRoot(ordered[i - 1]), ordered[i]);
        }
    } else {
        int delimiter = max(getKey(a), getKey(b));
        Treap *left, *right;
        split(getRoot(a), left, right, delimiter);
    }
}

int query(Treap *a, Treap *b) {
    if (getRoot(a) != getRoot(b)) return -1;
    else {
        int aKey = getKey(a);
        int bKey = getKey(b);
        if (bKey < aKey) swap(aKey, bKey);
        if (aKey == bKey) return 0;

        if (getRoot(a)->cyclic) {
            int g = bKey - aKey - 1;
            int h = getCount(getRoot(a)) - (bKey + 1) + aKey;

            return min(g, h);
        } else {
            return bKey - aKey - 1;
        }
    }
}


int main() {
    srand((unsigned int) time(nullptr));

    unsigned int n, m, q;
    cin >> n >> m >> q;

    vector<Treap *> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Treap();
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        join(nodes[a - 1], nodes[b - 1]);
    }

    for (int i = 0; i < q; i++) {
        char cmd;
        int a, b;
        cin >> cmd >> a >> b;
        a -= 1;
        b -= 1;

        if (cmd == '+') {
            join(nodes[a], nodes[b]);
        } else if (cmd == '-') {
            divide(nodes[a], nodes[b]);
        } else if (cmd == '?') {
            cout << query(nodes[a], nodes[b]) << endl;
        }
    }
    return 0;
}