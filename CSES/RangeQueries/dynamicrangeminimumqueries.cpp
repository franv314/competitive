#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    void update(int p, int v) {
        p += s;
        arr[p] = v;
        for (p >>= 1; p; p >>= 1)
            arr[p] = min(arr[2 * p], arr[2 * p + 1]);
    }

    int query(int l, int r) {
        int ans = INT_MAX;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = min(ans, arr[l++]);
            if (r & 1) ans = min(ans, arr[--r]);
        }
        return ans;
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        copy(a.begin(), a.end(), arr.begin() + s);
        for (int i = s - 1; i; i--) arr[i] = min(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);

    while (q--) {
        int t, a, b; cin >> t >> a >> b;
        if (t == 1) {
            segtree.update(a - 1, b);
        } else {
            cout << segtree.query(a - 1, b) << '\n';
        }
    }
}