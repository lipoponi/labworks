#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct Treap {
    int value = 0, count = 1, priority = 0;
    bool hasZero = true;
    Treap *left = nullptr, *right = nullptr;

    explicit Treap(int value) : value(value), count(1) {
        hasZero = (value == 0);
        priority = ((rand() << 16) | rand());
        left = right = nullptr;
    }
};


inline int getCount(Treap *root) {
    return root == nullptr ? 0 : root->count;
}

inline int getKey(Treap *root) {
    if (root == nullptr) return -1;
    else return getCount(root->left);
}

inline bool getHasZero(Treap *root) {
    return root == nullptr ? false : root->hasZero;
}

inline void update(Treap *root) {
    if (root != nullptr) {
        root->count = 1 + getCount(root->left) + getCount(root->right);
        root->hasZero = (root->value == 0) || getHasZero(root->left) || getHasZero(root->right);
    }
}


Treap *merge(Treap *left, Treap *right) {
    if (left == nullptr || right == nullptr) {
        return left == nullptr ? right : left;
    } else if (left->priority < right->priority) {
        right->left = merge(left, right->left);
        update(right->left);
        update(right);
        return right;
    } else {
        left->right = merge(left->right, right);
        update(left->right);
        update(left);
        return left;
    }
}

void split(Treap *root, Treap *&left, Treap *&right, int key) {
    if (root == nullptr) left = right = nullptr;
    else if (getKey(root) < key) {
        key -= 1 + getKey(root);
        split(root->right, root->right, right, key);
        left = root;
    } else {
        split(root->left, left, root->left, key);
        right = root;
    }

    update(left);
    update(right);
}

void removeZero(Treap *&root) {
    if (root == nullptr) return;

    if (getHasZero(root)) {
        if (getHasZero(root->left)) removeZero(root->left);
        else if (root->value == 0) {
            Treap *tmp = root;
            root = merge(root->left, root->right);
            delete tmp;
        } else removeZero(root->right);
    }

    update(root);
}

void insert(Treap *&root, int position, int value) {
    Treap *left, *right;
    split(root, left, right, position);
    removeZero(right);
    root = merge(merge(left, new Treap(value)), right);
}


Treap *build(int size) {
    Treap *root = nullptr;
    for (int i = 0; i < size; i++) {
        root = merge(root, new Treap(0));
    }
    return root;
}

void toVector(Treap *root, vector<int> &v) {
    if (root == nullptr) return;

    toVector(root->left, v);
    v.push_back(root->value);
    toVector(root->right, v);
}


int main() {
    int n, m;
    cin >> n >> m;
    Treap *root = build(n + m);

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int l;
        cin >> l;
        insert(root, l - 1, i);
    }

    toVector(root, ans);
    int w = 0;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] != 0) w = i + 1;
    }

    cout << w << endl;
    for (int i = 0; i < w; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}