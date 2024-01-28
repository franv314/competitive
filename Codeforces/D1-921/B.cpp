#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Line { long long m = 0, q = 0; };
    vector<long long> arr;
    vector<bool> has_lazy;
    vector<Line> lazy;
    int s;

    void push(int n, int nb, int ne) {
        if (!has_lazy[n]) return;
        
        long long set = lazy[n].q * (ne - nb)
                      + lazy[n].m * ((long long)ne * (ne - 1) - (long long)nb * (nb - 1)) / 2;
        arr[n] = set;

        if (nb + 1 != ne) {
            lazy[2 * n].m = lazy[n].m;
            lazy[2 * n].q = lazy[n].q;
            lazy[2 * n + 1].m = lazy[n].m;
            lazy[2 * n + 1].q = lazy[n].q;

            has_lazy[2 * n] = true;
            has_lazy[2 * n + 1] = true;
        }

        lazy[n].m = lazy[n].q = 0;
        has_lazy[n] = false;
    }

    void set_range(int l, int r, long long m, long long q, int n, int nb, int ne) {
        push(n, nb, ne);
        if (ne <= l || nb >= r) return;
        if (l <= nb && ne <= r) {
            lazy[n].m = m;
            lazy[n].q = q;
            has_lazy[n] = true;
            push(n, nb, ne);
            return;
        }

        set_range(l, r, m, q, 2 * n, nb, (nb + ne) / 2);
        set_range(l, r, m, q, 2 * n + 1, (nb + ne) / 2, ne);

        arr[n] = arr[2 * n] + arr[2 * n + 1];
    }

    long long query(int l, int r, int n, int nb, int ne) {
        push(n, nb, ne);
        if (ne <= l || nb >= r) return 0;
        if (l <= nb && ne <= r) return arr[n];

        return query(l, r, 2 * n, nb, (nb + ne) / 2)
             + query(l, r, 2 * n + 1, (nb + ne) / 2, ne);
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
        has_lazy.resize(2 * s);
        lazy.resize(2 * s);
    }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> X(m), V(m);
    for (auto &x: X) cin >> x;
    for (auto &v: V) cin >> v;

    map<int, int> hb;
    hb[0] = 0;
    hb[n + 1] = 0;

    SegTree segtree(n + 1);

    auto add_harbour = [&](int x, int v) {
        hb[x] = v;
        auto it = hb.find(x);
        auto p = prev(it);
        auto n = next(it);

        segtree.set_range(p->first + 1, x, -p->second, (long long)p->second * x, 1, 0, segtree.s);
        segtree.set_range(x + 1, n->first, -v, (long long)v * n->first, 1, 0, segtree.s);
        segtree.set_range(x, x + 1, 0, 0, 1, 0, segtree.s);
    };

    for (int i = 0; i < m; i++) {
        add_harbour(X[i], V[i]);
    }

    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            add_harbour(x, y);
        } else {
            cout << segtree.query(x, y + 1, 1, 0, segtree.s) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}