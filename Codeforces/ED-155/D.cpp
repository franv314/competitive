#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    
    for (auto &x: a) cin >> x;
    
    int ans = 0;
    
    for (int bit = 0; bit < 30; bit++) {
        vector<int> ba(n), pxor(n + 1);
        transform(a.begin(), a.end(), ba.begin(), [&](int x){ return (x >> bit) & 1; });
        for (int i = 0; i < n; i++) pxor[i + 1] = pxor[i] ^ ba[i];
        
        int sum_odd = 0, cnt_odd = 0;
        int sum_even = 0, cnt_even = 0;
        
        for (int i = 0; i <= n; i++) {
            if (pxor[i] & 1) {
                (sum_odd += i) %= MOD;
                cnt_odd++;
            } else {
                (sum_even += i) %= MOD;
                cnt_even++;
            }
        }
        
        int cnt = 0;
        for (int i = 0; i <= n; i++) {
            if (pxor[i] & 1) {
                (sum_odd += (MOD - i)) %= MOD;
                (cnt_odd += (MOD - 1)) %= MOD;
            } else {
                (sum_even += (MOD - i)) %= MOD;
                (cnt_even += (MOD - 1)) %= MOD;
            }
            
            if (pxor[i] & 1) {
                int am = (sum_even - ((long long)i * cnt_even % MOD) + MOD) % MOD;
                (cnt += am) %= MOD;
            } else {
                int am = (sum_odd - ((long long)i * cnt_odd % MOD) + MOD) % MOD;
                (cnt += am) %= MOD;
            }
        }
        
        int tot = ((long long)cnt << bit) % MOD;
        (ans += tot) %= MOD;
    }
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}