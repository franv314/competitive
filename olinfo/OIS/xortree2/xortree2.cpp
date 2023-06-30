#include <bits/stdc++.h>
using namespace std;

#define MAXN 50'000

struct Trie {
    struct Node {
        int size;
        Node *c[2];

        Node() : size(0) { c[0] = c[1] = NULL; }
    } *root;
    int ma;

    int max_with(Node* node, int depth, int q, int val) {
        if (depth == -1) return q ^ val;
        int mask = 1 << depth;
        if (q & mask) {
            if (node->c[0] != NULL) return max_with(node->c[0], depth - 1, q, val);
            return max_with(node->c[1], depth - 1, q, val | mask);
        } else {
            if (node->c[1] != NULL) return max_with(node->c[1], depth - 1, q, val | mask);
            return max_with(node->c[0], depth - 1, q, val);
        }
    }

    void insert(int x, int depth, Node *node) {
        node->size++;
        if (depth == -1) return;

        int dir = (bool)(x & (1 << depth));
        if (node->c[dir] == NULL) node->c[dir] = new Node();
        insert(x, depth - 1, node->c[dir]);
    }

    void erase(int x, int depth, Node *node) {
        node->size--;
        if (depth == -1) return;

        int dir = (bool)(x & (1 << depth));
        if (node->c[dir]->size == 1) node->c[dir] = NULL;
        else erase(x, depth - 1, node->c[dir]);
    }

    Trie() : ma(0) { root = new Node(); }
};

class SegTree {
    struct Node {
        vector<int> add;
        int nb, ne;
        Node *lc, *rc;

        Node (int b, int e, Node *l, Node *r) :
            add(), nb(b), ne(e), lc(l), rc(r) { };
    } *root;
    Trie trie;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(nb, ne, lc, rc);
    }

    void add_range(int x, int l, int r, Node *node) {
        if (l >= node->ne || r <= node->nb) return;
        if (l <= node->nb && node->ne <= r) {
            node->add.push_back(x);
            return;
        }
        add_range(x, l, r, node->lc);
        add_range(x, l, r, node->rc);
    }

    void dfs(Node *node) {
        int old_ma = trie.ma;
        for (auto x: node->add) {
            trie.insert(x, 29, trie.root);
            trie.ma = max(trie.ma, trie.max_with(trie.root, 29, x, 0));
        }

        if (node->nb + 1 == node->ne) {
            cout << trie.ma << "\n";
        } else {
            dfs(node->lc);
            dfs(node->rc);
        }

        reverse(node->add.begin(), node->add.end());
        for (auto x: node->add) {
            trie.erase(x, 29, trie.root);
        }
        trie.ma = old_ma;
    }

public:

    void dfs() { dfs(root); }
    void add_range(int x, int l, int r) { add_range(x, l, r, root); }

    SegTree(int N) { root = build(0, N); }

};

vector<pair<int, int>> adj[MAXN];
bitset<MAXN> visited;

vector<int> dfs_ps(1);
int pos_in_dfs[MAXN];

void dfs(int node) {
    pos_in_dfs[node] = dfs_ps.size() - 1;
    visited.set(node);

    for (auto [c, w]: adj[node]) {
        if (!visited[c]) {
            dfs_ps.push_back(dfs_ps.back() ^ w);
            dfs(c);
            dfs_ps.push_back(dfs_ps.back() ^ w);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N, Q; cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs(0);

    SegTree tree(Q);
    map<int, int> ranges;
    for (int t = 0; t < Q; t++) {
        int p; cin >> p;
        int np = dfs_ps[pos_in_dfs[p - 1]];
        
        if (ranges.find(p) == ranges.end()) {
            ranges[p] = t;
        } else {
            tree.add_range(np, ranges[p], t);
            ranges.erase(p);
        }
    }
    for (auto [p, s]: ranges) {
        int np = dfs_ps[pos_in_dfs[p - 1]];
        tree.add_range(np, s, Q);
    }

    tree.dfs();
}