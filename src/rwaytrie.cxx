#include "rwaytrie.h"
#include <functional>

using namespace std;

Node::Node() : value(0) {
    for (int i = 0; i < SIZE_OF_NODE_ARRAY; i++) {
        next[i] = nullptr;
    }
}

RWayTrie::RWayTrie() : root(nullptr) {}

RWayTrie::~RWayTrie() {
    // Helper function to recursively delete nodes
    function<void(Node*)> deleteNode = [&](Node* node) {
        if (node == nullptr) return;
        for (int i = 0; i < Node::SIZE_OF_NODE_ARRAY; i++) {
            if (node->next[i] != nullptr) {
                deleteNode(node->next[i]);
            }
        }
        delete node;
        };
    deleteNode(root);
}

void RWayTrie::insert(const string& key, int val) {
    root = insert(root, key, val, 0);
}

Node* RWayTrie::insert(Node* x, const string& key, int val, int d) {
    if (x == nullptr) {
        x = new Node();
    }

    if (d == key.length()) {
        x->value = val;
        return x;
    }

    unsigned char c = key[d];
    x->next[c] = insert(x->next[c], key, val, d + 1);
    return x;
}

bool RWayTrie::contains(const string& key) {
    Node* node = get(root, key, 0);
    return node != nullptr && node->value != 0;
}

int RWayTrie::get(const string& key) {
    Node* node = get(root, key, 0);
    if (node == nullptr) return 0;
    return node->value;
}

Node* RWayTrie::get(Node* x, const string& key, int d) {
    if (x == nullptr) return nullptr;
    if (d == key.length()) return x;
    unsigned char c = key[d];
    return get(x->next[c], key, d + 1);
}

void RWayTrie::insertOrIncrement(const string& key) {
    int currentValue = get(key);
    insert(key, currentValue + 1);
}