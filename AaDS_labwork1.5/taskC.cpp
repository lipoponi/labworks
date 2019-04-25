#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Node {
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    int key, priority;
    unsigned int index;

    Node(unsigned int index, int key, int priority) : index(index), key(key), priority(priority) {}

    friend bool operator<(Node &a, Node &b) {
        return a.key < b.key;
    }
};

bool cmp(Node *a, Node *b) {
    return a->key < b->key;
}

int main() {
    unsigned int n;
    cin >> n;
    vector<Node *> nodes(n);
    for (unsigned int i = 0; i < n; i++) {
        int key, priority;
        cin >> key >> priority;
        nodes[i] = new Node(i, key, priority);
    }

    sort(nodes.begin(), nodes.end(), cmp);

    for (int i = 1; i < n; i++) {
        Node *selected = nodes[i - 1];

        while (selected->parent != nullptr && nodes[i]->priority < selected->priority) {
            selected = selected->parent;
        }

        if (nodes[i]->priority < selected->priority) {
            nodes[i]->left = selected;
            selected->parent = nodes[i];
        } else {
            nodes[i]->left = selected->right;
            if (nodes[i]->left != nullptr) {
                nodes[i]->left->parent = nodes[i];
            }
            nodes[i]->parent = selected;
            selected->right = nodes[i];
        }
    }

    vector<Node *> assoc(n);

    for (int i = 0; i < n; i++) {
        assoc[nodes[i]->index] = nodes[i];
    }

    cout << "YES" << endl;
    for (Node *node : assoc) {
        cout << (node->parent == nullptr ? 0 : node->parent->index + 1) << " ";
        cout << (node->left == nullptr ? 0 : node->left->index + 1) << " ";
        cout << (node->right == nullptr ? 0 : node->right->index + 1) << endl;
    }
}