#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> ps(n + 1);
    for (int i = 1; i <= n; i++)
        ps[i] = ps[i - 1] + a[i - 1];
    
    vector<int> cc;
    for (int i = 0; i < n - 1; i++)
        if (a[i] == a[i + 1])
            cc.push_back(i);
    
    while (q--) {
        int l, r; cin >> l >> r; l--;

        int cnt_1 = ps[r] - ps[l];
        int cnt_0 = (r - l) - cnt_1;

        if (cnt_1 % 3 || cnt_0 % 3) {
            cout << "-1\n";
            continue;
        }

        auto it = lower_bound(cc.begin(), cc.end(), l);
        if (it != cc.end() && *it < r - 1) {
            cout << (r - l) / 3 << '\n';
        } else {
            cout << (r - l) / 3 + 1 << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
