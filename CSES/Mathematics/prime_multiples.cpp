#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n; cin >> n;
    int k; cin >> k;

    vector<long long> a(k);
    for (auto &x: a) cin >> x;

    long long ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        long long t = 1;
        for (int i = 0; i < k; i++) {
            if ((mask >> i) & 1) {
                long long ma = LLONG_MAX / t;
                if (a[i] > ma) goto next;
                t *= a[i];
            }
        }
        if (__builtin_popcount(mask) & 1) {
            ans += n / t;
        } else {
            ans -= n / t;
        }

        next:;
    }

    cout << ans << '\n';
}