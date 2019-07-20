#include <bits/stdc++.h>

using namespace std;

struct Node {
    int gain, count;
    Node *parent;
};

Node *join(Node *a, Node *b) {
    if (a == b) return a;
    if (b->count < a->count) swap(a, b);
    b->parent = a;
    a->count += b->count;
    b->gain -= a->gain;
}

Node *get(Node *a) {
    if (a->parent == nullptr) {
        return a;
    } else {
        if (a->parent->parent != nullptr) {
            Node *oldParent = a->parent;
            a->parent = get(a->parent);
            a->gain += oldParent->gain;
        }

        return a->parent;
    }
}

void add(Node *a, int v) {
    a->gain += v;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Node *> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node();
        nodes[i]->parent = nullptr;
        nodes[i]->count = 1;
        nodes[i]->gain = 0;
    }

    string cmd;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> cmd;
        switch (cmd[0]) {
            case 'j':
                scanf("%d %d", &a, &b);
                join(get(nodes[a - 1]), get(nodes[b - 1]));
                break;
            case 'a':
                scanf("%d %d", &a, &b);
                add(get(nodes[a - 1]), b);
                break;
            case 'g':
                scanf("%d", &a);
                get(nodes[a - 1]);
                Node *cur = nodes[a - 1];
                if (cur->parent == nullptr) {
                    printf("%d\n", cur->gain);
                } else {
                    printf("%d\n", cur->gain + cur->parent->gain);
                }
                break;
        }
    }
    return 0;
}
