#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    i64 x, m; cin >> x >> m;

    i64 cnt = 0;
    for (i64 y = 1; y <= min(m, 2 * x); y++) {
        if (y == x) continue;

        i64 res = x ^ y;
        if (x % res == 0 || y % res == 0) {
            cnt++;
        }
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
