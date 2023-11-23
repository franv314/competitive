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
    vector<int> ap(n), am(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ap[i] = x + i;
        am[i] = x - i;
    }

    SegTree seg_am(am), seg_ap(ap);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k, x; cin >> k >> x;
            k--;
            seg_am.update(k, x - k);
            seg_ap.update(k, x + k);
        } else {
            int k; cin >> k;
            k--;
            cout << min(
                seg_am.query(0, k) + k,
                seg_ap.query(k, n) - k
            ) << '\n';
        }
    }
}