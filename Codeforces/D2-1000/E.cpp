#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
mt19937 rng;

struct Node {
    int key, pri, size;
    i64 val, sum;
    Node *lc, *rc;

    void update() {
        sum = val;
        size = 1;

        if (lc) {
            size += lc->size;
            sum += lc->sum;
        }

        if (rc) {
            size += rc->size;
            sum += rc->sum;
        }
    }

    Node(int key, i64 val) : key(key), pri(rng()), size(1), val(val), sum(val), lc(), rc() { }
};

void merge(Node *l, Node *r, Node *&out) {
    if (l == nullptr)
        return void(out = r);
    if (r == nullptr)
        return void(out = l);
    
    if (l->pri < r->pri) {
        out = l;
        merge(l->rc, r, l->rc);
    } else {
        out = r;
        merge(l, r->lc, r->lc);
    }

    out->update();
}

// val goes right
void split(Node *in, Node *&l, Node *&r, int val) {
    if (in == nullptr)
        return void(l = r = in);
    
    if (in->key < val) {
        l = in;
        split(in->rc, l->rc, r, val);
    } else {
        r = in;
        split(in->lc, l, r->lc, val);
    }

    if (l) l->update();
    if (r) r->update();
}

pair<i64, int> query(Node *&node, int L, int R) {
    Node *l, *c, *r;
    split(node, l, node, L);
    split(node, c, r, R);

    pair<i64, int> ans = (c == nullptr) ? make_pair(0LL, 0) : make_pair(c->sum, c->size);

    merge(l, c, node);
    merge(node, r, node);

    return ans;
}

void update(Node *&node, int P, i64 D) {
    Node *l, *r;
    split(node, l, r, P);
    merge(l, new Node(P, D), node);
    merge(node, r, node);
}

int gsize(Node *node) {
    return node == nullptr ? 0 : node->size;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    i64 ans = 0;

    auto tt = [&](auto &tt, Node *node, Node *par, int lca_d) -> i64 {
        if (node == nullptr)
            return 0;
        
        auto [l_sum, l_size] = query(par, 0, node->key);
        auto [r_sum, r_size] = query(par, node->key, 1e9);

        i64 contrib = (2 * l_sum - l_size * (1LL + 2 * lca_d)) + ((2LL * (node->key - lca_d) - 1) * r_size);

        return contrib + tt(tt, node->lc, par, lca_d) + tt(tt, node->rc, par, lca_d);
    };

    auto tti = [&](auto &tti, Node *node, Node *&par) {
        if (node == nullptr)
            return;

        tti(tti, node->lc, par);
        tti(tti, node->rc, par);

        node->lc = node->rc = nullptr;
        node->update();

        Node *l, *r;
        split(par, l, r, node->key);
        merge(l, node, par);
        merge(par, r, par);
    };

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> Node* {
        Node *cur = nullptr;

        for (auto x: adj[node]) {
            if (x == par) continue;
            Node *child = dfs(dfs, x, node, d + 1);

            if (gsize(cur) < gsize(child))
                swap(cur, child);
            
            ans += tt(tt, child, cur, d);
            tti(tti, child, cur);
        }

        update(cur, d, d);
        return cur;
    };

    dfs(dfs, 0);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
