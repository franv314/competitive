#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long x, fy, gy;

    Info (long long x, long long fy, long long gy) : x(x), fy(fy), gy(gy) { }
    Info(int a, int b) : Info(b - a, b, 0) { }
    Info merge(const Info &o) const {
        long long nx = max(x, x + o.x - gy);
        return Info(nx, fy + o.fy, o.gy + max(0LL, gy - o.x));
    }
};

struct SegTree {
    struct Node {
        int nb, ne;
        Info info;
        Node *lc, *rc;

        Node(int nb, int ne, Info info, Node *lc, Node *rc) :
            nb(nb), ne(ne), info(info), lc(lc), rc(rc) { }
    } *root;

    Node* build(int nb, int ne, int a[], int b[]) {
        if (nb + 1 == ne) return new Node(nb, ne, Info(a[nb], b[nb]), NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, a, b);
        Node *rc = build((nb + ne) / 2, ne, a, b);
        return new Node(nb, ne, lc->info.merge(rc->info), lc, rc);
    }

    void update(int x, int a, int b, Node *node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->info = Info(a, b);
            return;
        }
        update(x, a, b, node->lc);
        update(x, a, b, node->rc);
        node->info = node->lc->info.merge(node->rc->info);
    }

    void dfs(Node *node) {
        if (node == NULL) return;
        
        cout << node->nb << " " << node->ne << endl;
        cout << "\t" << node->info.x << " " << node->info.fy << " " << node->info.gy << endl;
        dfs(node->lc);
        dfs(node->rc);
    }

public:

    void dfs() { dfs(root); }
    void update(int x, int a, int b) { update(x, a, b, root); }
    Info query() { return root->info; }

    SegTree(vector<int> &a, vector<int> &b) {
        root = build(0, a.size(), a.data(), b.data());
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    vector<long long> c(n - 1);

    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    for (auto &x: c) cin >> x;

    SegTree segtree(a, b);

    while (q--) {
        int p, x, y; cin >> p >> x >> y;
        long long z; cin >> z;
        p--;

        segtree.update(p, x, y);
        Info info = segtree.query();

        cout << (0 >= info.x ? info.fy : info.fy - info.x) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}