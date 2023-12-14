#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long sum, pref, suff, sub;

    Info(long long sum, long long pref, long long suff, long long sub)
        : sum(sum), pref(pref), suff(suff), sub(sub) { }
    Info(long long x) : Info(x, max(0LL, x), max(0LL, x), max(0LL, x)) { }
    Info() : Info(0, 0, 0, 0) { }
};

Info merge(const Info &a, const Info &b) {
    return {
        a.sum + b.sum,
        max(a.pref, a.sum + b.pref),
        max(b.suff, b.sum + a.suff),
        max({a.sub, b.sub, a.suff + b.pref})
    };
}

struct SegTree {
    vector<Info> arr;
    int s;

    void update(int p, int v) {
        p += s;
        arr[p] = Info(v);
        for (p >>= 1; p; p >>= 1)
            arr[p] = merge(arr[2 * p], arr[2 * p + 1]);
    }

    Info query(int l, int r) {
        Info ans_l, ans_r;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = merge(ans_l, arr[l++]);
            if (r & 1) ans_r = merge(arr[--r], ans_r);
        }
        return merge(ans_l, ans_r);
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++) arr[i + s] = Info(a[i]);
        for (int i = s - 1; i; i--) arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);

    while (q--) {
        int k, x; cin >> k >> x;
        segtree.update(k - 1, x);
        cout << segtree.query(0, n).sub << '\n';
    }
}