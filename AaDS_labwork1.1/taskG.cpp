#include <bits/stdc++.h>

using namespace std;

struct Node {
    int min, max, count;
    Node *parent, *cached;
};

Node *join(Node *a, Node *b) {
    if (a == b) return a;
    if (b->count < a->count) swap(a, b);
    b->parent = a;
    a->min = std::min(a->min, b->min);
    a->max = std::max(a->max, b->max);
    a->count += b->count;
}

Node *get(Node *a) {
    if (a->parent == nullptr) {
        return a;
    } else {
        if (a->parent->parent != nullptr) {
            a->parent = get(a->parent);
        }

        return a->parent;
    }
}

int main() {
    int n;
    cin >> n;
    vector<Node *> nodes(n);

    for (int i = 0; i < n; i++) {
        nodes[i] = new Node();
        nodes[i]->min = i + 1;
        nodes[i]->max = i + 1;
        nodes[i]->count = 1;
        nodes[i]->parent = nullptr;
        nodes[i]->cached = nullptr;
    }

    string cmd;
    int a, b;
    while (cin >> cmd) {
        switch (cmd[0]) {
            case 'u':
                scanf("%d %d", &a, &b);
                join(get(nodes[a-1]), get(nodes[b-1]));
                break;
            case 'g':
                scanf("%d", &a);
                Node *rep = get(nodes[a-1]);
                printf("%d %d %d\n", rep->min, rep->max, rep->count);
                break;
        }
    }
    return 0;
}