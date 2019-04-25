#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

struct Treap {
    char value;
    int count, priority, number;
    unsigned int exists;
    Treap *left, *right;

    explicit Treap(char value, int number) : value(value), number(number), count(number) {
        exists = (unsigned int) (1 << (value - 'a'));

        count = number;
        priority = (rand() << 16) | rand();
        left = right = nullptr;
    }
};


inline int getCount(Treap *root) {
    return root == nullptr ? 0 : root->count;
}

inline int getLowerKey(Treap *root) {
    if (root == nullptr) return -1;
    else return getCount(root->left);
}

inline int getHigherKey(Treap *root) {
    if (root == nullptr) return -1;
    else return getCount(root->left) + root->number - 1;
}

inline void update(Treap *root) {
    if (root != nullptr) {
        root->count = root->number + getCount(root->left) + getCount(root->right);
        root->exists = (unsigned int) (1 << (root->value - 'a'));
        if (root->left != nullptr) root->exists |= root->left->exists;
        if (root->right != nullptr) root->exists |= root->right->exists;
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
    else if (key <= getLowerKey(root)) {
        split(root->left, left, root->left, key);
        right = root;
    } else if (key <= getHigherKey(root)) {
        int l = key - getLowerKey(root);
        left = merge(root->left, new Treap(root->value, l));
        right = merge(new Treap(root->value, root->number - l), root->right);
    } else {
        key -= getHigherKey(root) + 1;
        split(root->right, root->right, right, key);
        left = root;
    }

    update(left);
    update(right);
}


void insert(Treap *&root, int index, int number, char value) {
    Treap *left, *right;
    split(root, left, right, index);
    root = merge(merge(left, new Treap(value, number)), right);
}

void remove(Treap *&root, int index, int number) {
    Treap *left, *mid, *right;
    split(root, left, mid, index);
    split(mid, mid, right, number);
    root = merge(left, right);
}

int query(Treap *&root, int index_1, int index_2) {
    Treap *left, *mid, *right;
    split(root, mid, right, index_2);
    split(mid, left, mid, index_1);
    int result = 0;
    if (mid != nullptr) for (int i = 0; i < 26; i++) result += (bool) (mid->exists & (1 << i));
    root = merge(merge(left, mid), right);
    return result;
}


int main() {
    srand(time(nullptr));
    int n;
    cin >> n;
    Treap *root = nullptr;

    for (int i = 0; i < n; i++) {
        char cmd;
        cin >> cmd;

        if (cmd == '+') {
            int index, number;
            char letter;
            cin >> index >> number >> letter;
            insert(root, index - 1, number, letter);
        } else if (cmd == '-') {
            int index, number;
            cin >> index >> number;
            remove(root, index - 1, number);
        } else if (cmd == '?') {
            int index_1, index_2;
            cin >> index_1 >> index_2;
            cout << query(root, index_1 - 1, index_2) << endl;
        }
    }
    return 0;
}