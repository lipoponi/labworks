#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    int number = 0;
    int count = 1;
    Node *parent = nullptr, *left = nullptr, *right = nullptr;
    Node *from = this, *to = this;

    Node() = default;

    Node(Node *from, Node *to) : from(from), to(to) {}
};

vector<Node *> nodes;
unordered_map<Node *, unordered_map<Node *, Node *>> steps;

class ST {
private:
    inline static void update(Node *node) {
        if (node == nullptr) return;

        node->count = 1;
        if (node->left != nullptr) node->count += node->left->count;
        if (node->right != nullptr) node->count += node->right->count;
    }

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
        update(node);
        update(x);

        x->parent = p;
        node->parent = x;
        if (m != nullptr) m->parent = node;
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
        update(node);
        update(x);

        x->parent = p;
        node->parent = x;
        if (m != nullptr) m->parent = node;
    }

    static Node *rightest(Node *node) {
        if (node == nullptr) return nullptr;
        if (node->right == nullptr) return node;
        return rightest(node->right);
    }

public:
    static void splay(Node *node) {
        if (node == nullptr) return;

        while (node->parent != nullptr) {
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
    }

    inline static Node *cutoff(Node *node) {
        ST::splay(node);

        Node *result = node->right;
        if (node->right != nullptr) {
            node->right->parent = nullptr;
            node->right = nullptr;
        }
        update(node);

        return result;
    }

    inline static Node *merge(Node *u, Node *v) {
        if (u == nullptr || v == nullptr) return u == nullptr ? v : u;

        splay(u);
        Node *p = rightest(u);
        v->parent = p;
        p->right = v;
        while (p != u) {
            update(p);
            p = p->parent;
        }
        update(u);

        return u;
    }

    inline static void print(Node *v) {
        if (v == nullptr) return;
        print(v->left);
        cout << "[" << v->from->number << " " << v->to->number << "]";
        print(v->right);
    }
};

class ET {
public:
    static void link(Node *u, Node *v) {
        ST::splay(u);
        ST::splay(v);

        Node *a = u;
        Node *b = ST::cutoff(u);
        Node *c = v;
        Node *d = ST::cutoff(v);

        Node *uv = new Node(u, v);
        Node *vu = new Node(v, u);
        steps[u][v] = uv;
        steps[v][u] = vu;

        Node *ba = ST::merge(b, a);
        Node *dc = ST::merge(d, c);
        Node *bauv = ST::merge(ba, uv);
        Node *dcvu = ST::merge(dc, vu);
        ST::merge(bauv, dcvu);
    }

    static void cut(Node *u, Node *v) {
        Node *uv = steps[u][v];
        Node *vu = steps[v][u];
        steps[u].erase(v);
        steps[v].erase(u);

        ST::splay(uv);
        Node *uvl = uv->left, *uvr = uv->right;
        if (uvl) uvl->parent = nullptr;
        if (uvr) uvr->parent = nullptr;

        ST::splay(vu);

        Node *a = nullptr, *b = nullptr, *c = nullptr;
        if (uvl != nullptr) {
            if (uvr == nullptr || vu == uvl || uvl->parent != nullptr) {
                a = vu->left;
                b = vu->right;
                c = uvr;
            }
        }
        if (uvr != nullptr) {
            if (uvl == nullptr || vu == uvr || uvr->parent != nullptr) {
                a = uvl;
                b = vu->left;
                c = vu->right;
            }
        }

        if (a) a->parent = nullptr;
        if (b) b->parent = nullptr;
        if (c) c->parent = nullptr;

        ST::merge(a, c);
    }

    static int size(Node *v) {
        ST::splay(v);
        return (v->count + 2) / 3;
    }

    static void print(Node *v) {
        ST::splay(v);
        cout << v->count << ": ";
        ST::print(v);
    }
};


int main() {
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif

    int n;
    cin >> n;

    nodes.resize(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node;
        nodes[i]->number = i;
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
#ifdef DEBUG
        for (int i = 0; i < n; i++) {
            ET::print(nodes[i]);
            cout << endl;
        }
#endif

        cout << endl;
        string command;
        cin >> command;

        if (command == "link") {
            int u, v;
            cin >> u >> v;
            u--, v--;

            ET::link(nodes[u], nodes[v]);
        } else if (command == "cut") {
            int u, v;
            cin >> u >> v;
            u--, v--;

            ET::cut(nodes[u], nodes[v]);
        } else if (command == "size") {
            int v;
            cin >> v;
            v--;

            cout << ET::size(nodes[v]) << endl;
        }
    }
    return 0;
}