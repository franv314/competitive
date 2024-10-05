#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    void set(int p, int v) {
        p += s;
        arr[p] = v;
        for (p >>= 1; p; p >>= 1) {
            arr[p] = arr[2 * p] + arr[2 * p + 1];
        }
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += arr[l++];
            if (r & 1) ans += arr[--r];
        }
        return ans;
    }

    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        arr.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    
    vector<int> h(n);
    vector<pair<int, int>> changes(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        changes[i] = {h[i], i};
    }

    vector<array<int, 4>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i][1] >> queries[i][2] >> queries[i][0];
        queries[i][1]--;
        queries[i][3] = i;
    }

    sort(queries.begin(), queries.end());
    sort(changes.begin(), changes.end());

    SegTree segtree(n);
    vector<int> ans(q);

    int pos = 0;
    for (auto [x, l, r, idx]: queries) {
        while (pos < n && changes[pos].first <= x) {
            segtree.set(changes[pos].second, 0);
            if (changes[pos].second < n - 1 && h[changes[pos].second + 1] > x) {
                segtree.set(changes[pos].second + 1, 1);
            }
            pos++;
        }

        ans[idx] = segtree.query(l, r);
        if (h[l] > x && (l == 0 || h[l - 1] > x)) ans[idx]++;
    }

    for (auto x: ans) cout << x << '\n';
}