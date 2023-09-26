#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    const int s = 1 << 17;
    vector<long long> arr;

    void ch_min(int pos, long long x) {
        for (pos += s; pos; pos >>= 1) {
            arr[pos] = min(arr[pos], x);
        }
    }

    long long get_min(int l, int r) {
        long long ans = LLONG_MAX;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = min(ans, arr[l++]);
            if (r & 1) ans = min(ans, arr[--r]);
        }
        return ans;
    }

    SegTree(int size) : arr(1 << 18, LLONG_MAX) { }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, D; cin >> N >> D;
    vector<int> L(N), P(N), S(N), T(N);

    for (int i = 0; i < N; i++) {
        cin >> L[i] >> P[i] >> S[i] >> T[i];
    }

    vector<int> Pm(N);
    for (int i = 0; i < N; i++) {
        Pm[i] = P[i] + D * i;
    }
    sort(Pm.begin(), Pm.end());
    Pm.resize(unique(Pm.begin(), Pm.end()) - Pm.begin());

    SegTree segtree(Pm.size());
    int pos = lower_bound(Pm.begin(), Pm.end(), P[0]) - Pm.begin();
    segtree.ch_min(pos, S[0]);
    
    long long last;

    for (int i = 1; i < N; i++) {
        last = -1;
        int l = lower_bound(Pm.begin(), Pm.end(), L[i] + D * i) - Pm.begin();
        long long mi = segtree.get_min(l, Pm.size());

        if (mi == LLONG_MAX) continue;
        last = mi + T[i] - (mi - S[i] + T[i]) % T[i];
        int pos = lower_bound(Pm.begin(), Pm.end(), P[i] + D * i) - Pm.begin();
        segtree.ch_min(pos, last);
    }

    cout << last << '\n';
}