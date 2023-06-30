#include <bits/stdc++.h>
using namespace std;

int repr(char c) {
    return c - 'a';
}

struct Node {
    int children_no;
    int children_upd;
    Node *parent;
    Node *children[27];
} nodes[2'200'000];

int no;

class Trie {
    Node *root;

    Node *insert(const char *str, Node *node) {
        int child = repr(*str);
        if (node->children[child] == NULL) {
            node->children_no++;

            node->children[child] = &nodes[no++];
            node->children[child]->parent = node;
        }
        
        if (child != 26) {
            return insert(str + 1, node->children[child]);
        }
        return node;
    }

public:

    Node* insert(string S) {
        return insert(S.c_str(), root);
    }

    void update(Node *node, int &count) {
        if (node == NULL) return;
        if (++node->children_upd < node->children_no) return;
        
        count -= node->children_no - 1;
        update(node->parent, count);
    }

    Trie() {
        root = &nodes[no++];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<Node*> S(N);
    Trie trie;

    trie.insert("{");
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        S[i] = trie.insert(s + '{');
    }

    int count = 0;
    for (auto node: S) {
        count++;
        trie.update(node, count);
        cout << count << "\n";
    }
}