#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct SegTree {
    vector<i64> arr;
    int s;

    void set(int p, int v) {
        p += s;
        arr[p] = v;
        for (p >>= 1; p; p >>= 1) {
            arr[p] = arr[2 * p] + arr[2 * p + 1];
        }
    }

    i64 query(int l, int r) {
        i64 ans = 0;
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

void solve() {
    int N; cin >> N;
    vector<i64> A(N);
    for (auto &x: A) cin >> x;

    int Q; cin >> Q;
    vector<array<int, 3>> queries(Q);
    vector<i64> ans(Q);

    for (int i = 0; i < Q; i++) {
        cin >> queries[i][1] >> queries[i][0];
        queries[i][1]--;
        queries[i][2] = i;
    }
    sort(queries.begin(), queries.end());

    SegTree segtree(N);
    vector<int> updates;
    int curr = 0;

    auto update = [&](int idx) {
        updates.push_back(idx);

        for (int i = 0; i < updates.size(); i++) {
            int p = updates[i];
            if (A[idx] % (idx + 1 - p) != 0) {
                if (i == updates.size() - 1) {
                    updates.pop_back();
                } else {
                    updates[i] = updates.back();
                    updates.pop_back();
                    i--;
                }
            } else {
                segtree.set(p, idx + 1);
            }
        }
    };

    for (auto [r, l, idx]: queries) {
        while (curr < r) {
            update(curr++);
        }
        i64 sum_r = segtree.query(l, r);
        i64 sum_l = ((i64)r * (r - 1) - (i64)l * (l - 1)) / 2;
        ans[idx] = sum_r - sum_l;
    }

    for (auto x: ans) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
}