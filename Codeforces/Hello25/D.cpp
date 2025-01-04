#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Info {
    i64 size, ans;
    i64 mi_p, ma_p, mi_s, ma_s;

    void dbg() const {
        cerr << size << " " << ans << endl;
        cerr << mi_p << " " << ma_p << " " << mi_s << " " << ma_s << endl;
    }
};

Info single(int val) {
    Info ans;
    ans.size = 1;
    ans.ans = -1;

    ans.ma_p = ans.ma_s = val - 1;
    ans.mi_p = ans.mi_s = val + 1;

    return ans;
}

Info merge(const Info &a, const Info &b) {
    Info ans;
    ans.size = a.size + b.size;
    ans.ans = max({a.ans, b.ans, a.ma_s - b.mi_p, b.ma_p - a.mi_s});
    
    ans.ma_p = max(a.ma_p, b.ma_p - a.size);
    ans.ma_s = max(b.ma_s, a.ma_s - b.size);

    ans.mi_p = min(a.mi_p, b.mi_p + a.size);
    ans.mi_s = min(b.mi_s, a.mi_s + b.size);

    return ans;
};

struct SegTree {
    vector<Info> arr;
    int s;

    void update(int p, int v) {
        p += s;
        arr[p] = single(v);
        for (p >>= 1; p; p >>= 1)
            arr[p] = merge(arr[2 * p], arr[2 * p + 1]);
    }

    int query(int l, int r) {
        optional<Info> ans_l, ans_r;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (ans_l) ans_l.value() = merge(ans_l.value(), arr[l]);
                else ans_l = arr[l];
                l++;
            }
            if (r & 1) {
                --r;
                if (ans_r) ans_r.value() = merge(arr[r], ans_r.value());
                else ans_r = arr[r];
            }
        }

        if (!ans_l) return ans_r.value().ans;
        if (!ans_r) return ans_l.value().ans;
        return merge(ans_l.value(), ans_r.value()).ans;
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++)
            arr[i + s] = single(a[i]);
        for (int i = s - 1; i; i--) {
            arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
        }
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);
    cout << segtree.query(0, n) + 1 << '\n';

    while (q--) {
        int p, v; cin >> p >> v;
        p--;

        segtree.update(p, v);
        cout << segtree.query(0, n) + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
