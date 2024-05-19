#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

int fexp(int base, int exp) {
    int ans = 1;
    do {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    } while (exp >>= 1);
    return ans;
}

void solve() {
    int A1, A2, A3; cin >> A1 >> A2 >> A3;

    if (A1 > A2)
        swap(A1, A2);
    
    if (A2 == A3) {
        if (A1 < A2) {
            int l = fexp(10, A1 - 1);
            int r = fexp(10, A1);

            int diff = (fexp(10, A2) - fexp(10, A2 - 1) + MOD) % MOD;

            int ans = ((long long)diff * (r - l + MOD) % MOD
                    - ((long long)r * (r - 1) % MOD - (long long)l * (l - 1) % MOD + MOD) * ((MOD + 1) / 2) % MOD + MOD) % MOD;

            cout << ans << '\n';
        } else {
            int l = fexp(10, A1 - 1);
            int r = (fexp(10, A1) - fexp(10, A2 - 1) + MOD) % MOD;

            int diff = (fexp(10, A2) - fexp(10, A2 - 1) + MOD) % MOD;

            int ans = ((long long)diff * (r - l + MOD) % MOD
                    - ((long long)r * (r - 1) % MOD - (long long)l * (l - 1) % MOD + MOD) * ((MOD + 1) / 2) % MOD + MOD) % MOD;

            cout << ans << '\n';
        }
    } else if (A2 + 1 == A3) {
        if (A1 < A2) {
            int l = fexp(10, A1 - 1);
            int r = fexp(10, A1);

            int ans = ((long long)r * (r - 1) % MOD - (long long)l * (l - 1) % MOD + MOD) * ((MOD + 1) / 2) % MOD;

            cout << ans << '\n'; 
        } else {
            int l = fexp(10, A1 - 1);
            int r = (fexp(10, A1) - fexp(10, A1 - 1) + MOD + 1) % MOD;
            int z = fexp(10, A2);

            int diff = (fexp(10, A2) - fexp(10, A2 - 1) + MOD) % MOD;

            int ans = (((long long)r * (r - 1) % MOD - (long long)l * (l - 1) % MOD + MOD) * ((MOD + 1) / 2) % MOD
                    + (long long)(z - r + MOD) * diff) % MOD;

            cout << ans << '\n'; 
        }
    } else {
        cout << "0\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}