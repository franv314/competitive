#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
constexpr int MOD = 998244353;

void solve() {
    i64 n; cin >> n;
    
    vector<i64> dp_is(n + 1), dp_not(n + 1), ps_not(n + 1);
    dp_is[n] = 1;
    dp_not[n] = 1;
    ps_not[n] = 1;

    for (int i = n - 1; i >= 2; i--) {
        i64 val_not = (dp_is[i + 1] + i * dp_not[i + 1]) % MOD;
        i64 val_is = ((i - 1) * ps_not[i + 1] + 1) % MOD;

        dp_is[i] = val_is;
        dp_not[i] = val_not;
        ps_not[i] = (ps_not[i + 1] + val_not) % MOD;
    }

    i64 ans = 1;
    for (int i = 3; i <= n; i++)
        ans = (ans + dp_is[i]) % MOD;
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
