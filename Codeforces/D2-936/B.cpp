#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int b, int e) {
    int ans = 1;
    do {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    } while (e >>= 1);
    return ans;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long ps = 0, min_ps = 0, max_s = 0;
    long long mod_sum = 0;
    for (auto x: a) {
        ps += x;
        max_s = max(max_s, ps - min_ps);
        min_ps = min(ps, min_ps);
    
        mod_sum = (mod_sum + x + MOD) % MOD;
    }

    cout << ((mod_sum - max_s % MOD + MOD) % MOD + (max_s % MOD) * fexp(2, k)) % MOD << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}