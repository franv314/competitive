#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    int n, k; cin >> n >> k;

    auto rec = [&](auto &&rec, int l, int r) -> pair<i64, i64> {
        int m = (l + r) / 2;
        int len = r - l + 1;

        if (len < k)
            return {0, 0};
        
        if (len % 2 == 0) {
            auto [cnt, val_l] = rec(rec, l, m);
            i64 val_r = val_l + cnt * (m + 1 - l);
            return {2 * cnt, val_l + val_r}; 
        } else {
            auto [cnt, val_l] = rec(rec, l, m - 1);
            i64 val_r = val_l + cnt * (m + 1 - l);
            return {2 * cnt + 1, val_l + val_r + m};
        }
    };

    cout << rec(rec, 1, n).second << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
