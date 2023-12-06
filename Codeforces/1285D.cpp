#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        Node *arr[2];
        Node() { arr[0] = arr[1] = NULL; }
    } *root;

    void insert(int val, int d, Node *node) {
        if (d == -1) return;
        if (node->arr[(val >> d) & 1] == NULL)
            node->arr[(val >> d) & 1] = new Node;

        insert(val, d - 1, node->arr[(val >> d) & 1]);
    }

    int dp(int d, Node *node) {
        if (node->arr[0] == NULL && node->arr[1] == NULL) return 0;
        if (node->arr[0] == NULL) return dp(d - 1, node->arr[1]);
        if (node->arr[1] == NULL) return dp(d - 1, node->arr[0]);
        return min(dp(d - 1, node->arr[0]), dp(d - 1, node->arr[1])) | (1 << d);
    }

public:

    void insert(int val) { insert(val, 30, root); }
    int dp() { return dp(30, root); }
    Trie() { root = new Node; }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    
    Trie trie;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        trie.insert(a);
    }

    cout << trie.dp() << '\n';
}