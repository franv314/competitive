#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    i64 a, b, k; cin >> a >> b >> k;
    i64 sum = a + b + k;

    auto check = [&](i64 m) -> bool {
        i64 c_a = (m - a % m) % m;
        i64 c_b = (m - b % m) % m;
        return c_a + c_b <= k;
    };

    vector<i64> divisors;
    for (i64 i = 1; i * i <= sum; i++) {
        if (sum % i)
            continue;
        divisors.push_back(i);
        if (i * i != sum)
            divisors.push_back(sum / i);
    }

    i64 ans = -1;
    for (auto x: divisors)
        if (check(x))
            ans = max(ans, x);
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}