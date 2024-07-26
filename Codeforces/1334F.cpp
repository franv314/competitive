#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

class SegTree {
    vector<i64> arr, lazy;
    int s;

    void push(int n, int nb, int ne) {
        if (lazy[n]) {
            arr[n] += lazy[n];

            if (nb + 1 != ne) {
                lazy[2 * n] += lazy[n];
                lazy[2 * n + 1] += lazy[n];
            }

            lazy[n] = 0;
        }
    }

    i64 query(int l, int r, int n, int nb, int ne) {
        push(n, nb, ne);
        if (nb >= r || ne <= l) return -1e18;
        if (l <= nb && ne <= r) return arr[n];
        return max(
            query(l, r, 2 * n, nb, (nb + ne) / 2),
            query(l, r, 2 * n + 1, (nb + ne) / 2, ne)
        );
    }

    void add(int l, int r, i64 x, int n, int nb, int ne) {
        push(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            lazy[n] = x;
            push(n, nb, ne);
            return;
        }

        add(l, r, x, 2 * n, nb, (nb + ne) / 2);
        add(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
    }

public:
    
    i64 query(int l, int r) { return query(l, r, 1, 0, s); }
    void add(int l, int r, i64 x) { add(l, r, x, 1, 0, s); }
    void set(int p, i64 x) { add(p, p + 1, x - query(p, p + 1), 1, 0, s); }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
        lazy.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n), p(n);
    for (auto &x: a) cin >> x;
    for (auto &x: p) cin >> x;

    int m; cin >> m;
    vector<int> b(m);
    for (auto &x: b) cin >> x;

    int pos_b = 0;
    for (auto x: a)
        if (pos_b < m && x == b[pos_b])
            pos_b++;

    if (pos_b != m)
        return cout << "NO\n", 0;

    SegTree segtree(b.size() + 1);
    segtree.add(1, b.size() + 1, 1e18);

    for (int i = 0; i < n; i++) {
        if (binary_search(b.begin(), b.end(), a[i])) {
            int pos = 1 + lower_bound(b.begin(), b.end(), a[i]) - b.begin();

            i64 new_cost = min(
                segtree.query(pos - 1, pos),
                segtree.query(pos, pos + 1) + min(p[i], 0)
            );

            segtree.add(0, pos, p[i]);
            segtree.add(pos + 1, b.size() + 1, min(0, p[i]));
            segtree.set(pos, new_cost);
        } else {
            int pos = 1 + upper_bound(b.begin(), b.end(), a[i]) - b.begin();
            segtree.add(0, pos, p[i]);
            segtree.add(pos, b.size() + 1, min(0, p[i]));
        }
    }

    cout << "YES\n";
    cout << segtree.query(b.size(), b.size() + 1) << '\n';
}