#include <bits/stdc++.h>
using namespace std;

int N;

struct SegTree {
    vector<long long> sum;
    vector<long long> ma;
    vector<pair<bool, long long>> lazy;
    int s;

    void update(int n, int nb, int ne) {
        if (lazy[n].first) {
            sum[n] = (long long)(ne - nb) * lazy[n].second;
            ma[n] = lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n] = lazy[2 * n + 1] = lazy[n];
            }
        } else {
            sum[n] += (long long)(ne - nb) * lazy[n].second;
            ma[n] += lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n].second += lazy[n].second;
                lazy[2 * n + 1].second += lazy[n].second;
            }
        }
        lazy[n] = {false, 0};
    }

    template<bool set>
    void update(int l, int r, int x, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            if (set) lazy[n] = {true, x};
            else lazy[n].second += x;

            update(n, nb, ne);
            return;
        }
        update<set>(l, r, x, 2 * n, nb, (nb + ne) / 2);
        update<set>(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        sum[n] = sum[2 * n] + sum[2 * n + 1];
        ma[n] = max(ma[2 * n], ma[2 * n + 1]);
    }

    long long query(int l, int r, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return 0;
        if (l <= nb && ne <= r) return sum[n];

        return query(l, r, 2 * n, nb, (nb + ne) / 2)
             + query(l, r, 2 * n + 1, (nb + ne) / 2, ne);
    }

    int lower_bound(int l, int x, int n, int nb, int ne) {
        update(n, nb, ne);
        if (ne <= l || ma[n] <= x) return N;
        if (nb + 1 == ne) return nb;
        int lv = lower_bound(l, x, 2 * n, nb, (nb + ne) / 2);
        if (lv != N) return lv;
        return lower_bound(l, x, 2 * n + 1, (nb + ne) / 2, ne);
    }

    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        sum.resize(2 * s);
        ma.resize(2 * s);
        lazy.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    N = n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l - 1, r, i);
    }

    sort(queries.rbegin(), queries.rend());

    vector<long long> ps(n + 1);
    for (int i = 1; i <= n; i++) ps[i] = ps[i - 1] + a[i - 1];
    
    SegTree segtree(n);
    vector<long long> answers(q);

    int curr_l = N;
    for (auto [l, r, i]: queries) {
        while (l < curr_l) {
            curr_l--;
            int sr = segtree.lower_bound(curr_l, a[curr_l], 1, 0, segtree.s);
            segtree.update<true>(curr_l, sr, a[curr_l], 1, 0, segtree.s);
        }
        answers[i] = segtree.query(l, r, 1, 0, segtree.s) - (ps[r] - ps[l]);
    }

    for (auto ans: answers) cout << ans << '\n';
}