#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Node {
    bool reversed = false;
    Node *parent = nullptr, *left = nullptr, *right = nullptr;
    Node *link = nullptr;
};

vector<Node *> nodes;


class ST {
private:
    inline static void rotateLeft(Node *node) {
        if (node == nullptr || node->right == nullptr) return;

        Node *p = node->parent;
        Node *x = node->right;
        Node *m = x->left;

        if (p != nullptr) {
            if (p->left == node) p->left = x;
            if (p->right == node) p->right = x;
        }

        x->left = node;
        node->right = m;

        x->parent = p;
        node->parent = x;
        if (m != nullptr) m->parent = node;

        x->link = node->link;
        node->link = nullptr;
    }

    inline static void rotateRight(Node *node) {
        if (node == nullptr || node->left == nullptr) return;

        Node *p = node->parent;
        Node *x = node->left;
        Node *m = x->right;

        if (p != nullptr) {
            if (p->left == node) p->left = x;
            if (p->right == node) p->right = x;
        }
        x->right = node;
        node->left = m;

        x->parent = p;
        node->parent = x;
        if (m != nullptr) m->parent = node;

        x->link = node->link;
        node->link = nullptr;
    }

    inline static void resolve(Node *node) {
        if (node == nullptr || !node->reversed) return;

        reverse(node->left);
        reverse(node->right);
        swap(node->left, node->right);
        node->reversed = false;
    }

    static void resolveFromRoot(Node *node) {
        if (node == nullptr) return;
        resolveFromRoot(node->parent);
        resolve(node);
    }

public:
    static void splay(Node *node) {
        if (node == nullptr) return;

        while (node->parent != nullptr) {
            if (node->parent->parent != nullptr) resolve(node->parent->parent);
            resolve(node->parent);
            resolve(node);

            if (node->parent->left == node) {
                if (node->parent->parent == nullptr) {
                    rotateRight(node->parent);
                } else if (node->parent->parent->left == node->parent) {
                    rotateRight(node->parent->parent);
                    rotateRight(node->parent);
                } else {
                    rotateRight(node->parent);
                    rotateLeft(node->parent);
                }
            } else {
                if (node->parent->parent == nullptr) {
                    rotateLeft(node->parent);
                } else if (node->parent->parent->right == node->parent) {
                    rotateLeft(node->parent->parent);
                    rotateLeft(node->parent);
                } else {
                    rotateLeft(node->parent);
                    rotateRight(node->parent);
                }
            }
        }

        resolve(node);
    }

    inline static void reverse(Node *node) {
        if (node == nullptr) return;
        node->reversed = !node->reversed;
    }
};

class LCT {
private:
    static void cutout(Node *node) {
        ST::splay(node);

        if (node->right != nullptr) {
            node->right->parent = nullptr;
            node->right->link = node;
            node->right = nullptr;
        }
    }

    static void expose(Node *node) {
        Node *u = node;

        cutout(u);
        while (u->link != nullptr) {
            Node *p = u->link;
            cutout(p);
            p->right = u;
            u->parent = p;
            u->link = nullptr;
            u = p;
        }

        cutout(node);
    }

    static void revert(Node *node) {
        expose(node);
        ST::splay(node);
        ST::reverse(node);
    }

    static void link(Node *u, Node *v) {
        u->link = v;
        expose(u);
    }

    static void cut(Node *u, Node *v) {
        expose(u);
        expose(v);
        u->link = nullptr;
        expose(u);
    }

public:
    static void linkEdge(Node *u, Node *v) {
        revert(u);
        link(u, v);
    }

    static void cutEdge(Node *u, Node *v) {
        revert(v);
        cut(u, v);
    }

    static bool connected(Node *a, Node *b) {
        expose(a);
        expose(b);

        ST::splay(a);
        if (a->link != nullptr) return true;
        return b->parent != nullptr;
    }
};


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif

    int n, m;
    cin >> n >> m;

    nodes.resize(n);
    for (auto &node : nodes) node = new Node;

    for (int i = 0; i < m; i++) {
        string command;
        int v, u;
        cin >> command >> v >> u;
        v--, u--;

        if (command == "link") {
            LCT::linkEdge(nodes[v], nodes[u]);
        } else if (command == "cut") {
            LCT::cutEdge(nodes[v], nodes[u]);
        } else if (command == "connected") {
            bool connected = LCT::connected(nodes[v], nodes[u]);
            cout << (connected ? 1 : 0) << endl;
        }
    }
    return 0;
}