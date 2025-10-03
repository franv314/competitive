#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    auto moves = [&](int x) {
        for (int i = 1; ; i++)
            if (x < (1 << i) + 2)
                return i;
    };

    vector<int> ps_moves(n + 1);
    vector<int> good;

    for (int i = 1; i <= n; i++) {
        ps_moves[i] = ps_moves[i - 1] + moves(a[i - 1] + 1);
        if (moves(a[i - 1]) < moves(a[i - 1] + 1))
            good.push_back(i - 1);
    }

    while (q--) {
        int l, r; cin >> l >> r; l--;
        
        int ans = ps_moves[r] - ps_moves[l];
        
        auto cnt = lower_bound(good.begin(), good.end(), r) - lower_bound(good.begin(), good.end(), l);
        ans -= (cnt + 1) / 2;

        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}