#include <bits/stdc++.h>
using namespace std;

class SegTree {
    vector<vector<int>> arr;
    int sz, s;

    int bound(int l, int r, int x, int n, int nb, int ne) {
        if (nb >= r || ne <= l || arr[n].back() <= x) return sz;
        if (nb + 1 == ne) return nb;

        int lc = bound(l, r, x, 2 * n, nb, (nb + ne) / 2);
        if (lc != sz) return lc;
        return bound(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
    }

    int cnt(int n, int x) {
        return upper_bound(arr[n].begin(), arr[n].end(), x) - lower_bound(arr[n].begin(), arr[n].end(), x);
    }
public:
    
    int bound(int l, int r, int x) { return bound(l, r, x, 1, 0, s); }

    int query(int l, int r, int x) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += cnt(l++, x);
            if (r & 1) ans += cnt(--r, x);
        }
        return ans;
    }

    SegTree(vector<int> a) : sz(a.size()) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);
        for (int i = 0; i < sz; i++) arr[i + s].push_back(a[i]);
        for (int i = s - 1; i > 0; i--) {
            merge(arr[2 * i].begin(), arr[2 * i].end(), arr[2 * i + 1].begin(), arr[2 * i + 1].end(), back_inserter(arr[i]));
        }
    }
};

void solve() {
    string s; cin >> s;
    int n = s.size();

    vector<int> ps(n + 1);
    for (int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + (s[i] == '(' ? +1 : -1);
    }

    SegTree segtree(ps);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int r = segtree.bound(i, n + 1, 2 * ps[i]);
        ans += segtree.query(i + 1, r, ps[i]);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}