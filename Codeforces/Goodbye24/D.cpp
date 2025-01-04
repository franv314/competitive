#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
constexpr int MOD = 998244353;

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    vector<int> sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    i64 ans = 1;
    for (int i = 0; i < n; i++)
        ans = ans * min(sa[i], sb[i]) % MOD;
    
    cout << ans << ' ';

    while (q--) {
        int o, i; cin >> o >> i;
        i--;

        i64 old_contrib, new_contrib;
        if (o == 1) {
            int val = a[i];
            a[i]++;
            int pos = upper_bound(sa.begin(), sa.end(), val) - sa.begin() - 1;

            old_contrib = min(sa[pos], sb[pos]);
            sa[pos]++;
            new_contrib = min(sa[pos], sb[pos]);
        } else {
            int val = b[i];
            b[i]++;
            int pos = upper_bound(sb.begin(), sb.end(), val) - sb.begin() - 1;

            old_contrib = min(sa[pos], sb[pos]);
            sb[pos]++;
            new_contrib = min(sa[pos], sb[pos]);
        }

        ans = ans * fexp(old_contrib, MOD - 2) % MOD;
        ans = ans * new_contrib % MOD;

        cout << ans << ' ';
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
