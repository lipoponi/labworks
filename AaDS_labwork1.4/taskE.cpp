#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

struct Node;

int r;
int treeSize;
Node *tree;

inline int mod(int a, int b) {
    return a < b ? a : a % b;
}

struct Matrix {
    int a11, a12, a21, a22;

    friend Matrix operator*(Matrix left, Matrix right) {
        return (Matrix) {
                mod(left.a11 * right.a11 + left.a12 * right.a21, r),
                mod(left.a11 * right.a12 + left.a12 * right.a22, r),
                mod(left.a21 * right.a11 + left.a22 * right.a21, r),
                mod(left.a21 * right.a12 + left.a22 * right.a22, r)
        };
    }

    friend istream &operator>>(istream &is, Matrix &matrix) {
        is >> matrix.a11 >> matrix.a12 >> matrix.a21 >> matrix.a22;
        return is;
    }

    friend ostream &operator<<(ostream &os, Matrix matrix) {
        os << matrix.a11 << " " << matrix.a12 << endl;
        os << matrix.a21 << " " << matrix.a22 << endl;
        return os;
    }

    void print() {
        printf("%d %d\n%d %d\n\n", a11, a12, a21, a22);
    }
} E = {1, 0, 0, 1};

struct Node {
    int left, right;
    Matrix val;
};

void build(Matrix *a, int n) {
    treeSize = 1;
    while (treeSize < n) treeSize *= 2;
    tree = new Node[treeSize * 2 - 1];
    for (int i = 0; i < treeSize; i++) {
        tree[treeSize - 1 + i] = {i, i + 1, E};
    }
    for (int i = 0; i < n; i++) {
        tree[treeSize - 1 + i].val = a[i];
    }
    for (int i = treeSize - 2; 0 <= i; i--) {
        tree[i] = {
                tree[i * 2 + 1].left,
                tree[i * 2 + 2].right,
                tree[i * 2 + 1].val * tree[i * 2 + 2].val
        };
    }
}

Matrix query(int node, int &a, int &b) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (a <= left && right <= b) {
        return tree[node].val;
    } else if (right <= a || b <= left) {
        return E;
    } else {
        return query(node * 2 + 1, a, b) * query(node * 2 + 2, a, b);
    }
}

int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("crypto.in", "r+", stdin);
    freopen("crypto.out", "w+", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int n, m;
    cin >> r >> n >> m;

    auto *a = new Matrix[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(a, n);

#ifdef DEBUG
    for (int i = 0; i < treeSize * 2 - 1; i++) {
        printf("[%d; %d)\n", tree[i].left, tree[i].right);
        cout << tree[i].val << endl;
    }
#endif

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        query(0, l, r).print();
    }
    return 0;
}