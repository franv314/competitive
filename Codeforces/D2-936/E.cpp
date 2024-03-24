#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int base, int exp) {
    int ans = 1;
    do {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    } while (exp >>= 1);
    return ans;
}

void solve() {
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<int> p(m1), s(m2);
    for (auto &x: p) cin >> x;
    for (auto &x: s) cin >> x;

    if (p.back() != s.front()) return void(cout << "0\n");
    if (p.front() != 1 || s.back() != n) return void(cout << "0\n");
    
    long long ans = 1;

    for (int i = 1; i < n; i++) ans = ans * i % MOD;
    for (int i = 1; i < p.back(); i++) ans = ans * fexp(i, MOD - 2) % MOD;
    for (int i = 1; i <= n - p.back(); i++) ans = ans * fexp(i, MOD - 2) % MOD;

    for (int i = m1 - 2; i >= 0; i--) {
        int max_choice = p[i + 1] - 1;
        for (int j = 1; j < p[i + 1] - p[i]; j++) {
            ans = (ans * (max_choice - j)) % MOD;
        }
    }

    reverse(s.begin(), s.end());
    for (auto &x: s) x = n + 1 - x;
    
    for (int i = m2 - 2; i >= 0; i--) {
        int max_choice = s[i + 1] - 1;
        for (int j = 1; j < s[i + 1] - s[i]; j++) {
            ans = (ans * (max_choice - j)) % MOD;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}