#include <bits/stdc++.h>
using namespace std;

int N;

struct SegTree {
    vector<long long> sum;
    vector<pair<bool, long long>> lazy;
    int s;

    void update(int n, int nb, int ne) {
        if (lazy[n].first) {
            sum[n] = (long long)(ne - nb) * lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n] = lazy[2 * n + 1] = lazy[n];
            }
        } else {
            sum[n] += (long long)(ne - nb) * lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n].second += lazy[n].second;
                lazy[2 * n + 1].second += lazy[n].second;
            }
        }
        lazy[n] = {false, 0};
    }

    template<bool set>
    void change(int l, int r, int x, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            if (set) lazy[n] = {true, x};
            else lazy[n].second += x;

            update(n, nb, ne);
            return;
        }
        change<set>(l, r, x, 2 * n, nb, (nb + ne) / 2);
        change<set>(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        sum[n] = sum[2 * n] + sum[2 * n + 1];
    }

    long long query(int l, int r, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return 0;
        if (l <= nb && ne <= r) return sum[n];

        return query(l, r, 2 * n, nb, (nb + ne) / 2)
             + query(l, r, 2 * n + 1, (nb + ne) / 2, ne);
    }

    template<bool set>
    void change(int l, int r, int x) { change<set>(l, r, x, 1, 0, s); }
    long long query(int l, int r) { return query(l, r, 1, 0, s); }

    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        sum.resize(2 * s);
        lazy.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    SegTree segtree(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        segtree.change<true>(i, i + 1, x);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            segtree.change<false>(l - 1, r, x);
        } else if (t == 2) {
            int l, r, x; cin >> l >> r >> x;
            segtree.change<true>(l - 1, r, x);
        } else {
            int l, r; cin >> l >> r;
            cout << segtree.query(l - 1, r) << '\n';
        }
    }
}