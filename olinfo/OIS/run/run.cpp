#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    int lower_bound_r(int l, int r, int x, int n, int nb, int ne) {
        if (ne <= l || nb >= r || arr[n] >= x) return 1e9;
        if (nb + 1 == ne) return nb;
        int lq = lower_bound_r(l, r, x, 2 * n, nb, (nb + ne) / 2);
        if (lq != 1e9) return lq;
        return lower_bound_r(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
    }

    int lower_bound_l(int l, int r, int x, int n, int nb, int ne) {
        if (ne <= l || nb >= r || arr[n] >= x) return -1e9;
        if (nb + 1 == ne) return nb;
        int rq = lower_bound_l(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        if (rq != -1e9) return rq;
        return lower_bound_l(l, r, x, 2 * n, nb, (nb + ne) / 2);
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);
        for (int i = 0; i < a.size(); i++) arr[i + s] = a[i];
        for (int i = s - 1; i; i--) arr[i] = min(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> D(N);
    for (auto &d: D) cin >> d;

    SegTree segtree(D);
    vector<int> rightmost(N);
    for (int i = 0; i < N; i++) {
        rightmost[i] = min(N, segtree.lower_bound_r(i, N, D[i], 1, 0, segtree.s));
    }
    
    for (auto &d: D) d *= -1;
    segtree = SegTree(D);

    vector<int> leftmost(N);
    for (int i = 0; i < N; i++) {
        leftmost[i] = max(-1, segtree.lower_bound_l(0, i, D[i], 1, 0, segtree.s));
    }

    segtree = SegTree(leftmost);
    int ans = 0;

    for (int l = 0; l < N; l++) {
        int rmax = rightmost[l];
        int r_eff = segtree.lower_bound_l(l, rmax, l, 1, 0, segtree.s);
        ans = max(ans, r_eff - l + 1);
    }

    cout << ans << '\n';
}