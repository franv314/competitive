#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    i64 x, m; cin >> x >> m;

    auto x_mul_in_range = [&](i64 l, i64 r) -> i64 {
        i64 less_l = (l + x -1) / x;
        i64 less_r = (r + x - 1) / x;
        return less_r - less_l - (l <= x && x < r);
    };

    i64 cnt = 0;
    i64 acc = 0;

    for (i64 b = 60; b >= 0; b--) {
        if ((m >> b) & 1) {
            i64 l, r;
            
            if ((x >> b) & 1) {
                l = acc + (1LL << b);
                r = l + (1LL << b);
            } else {
                l = acc;
                r = l + (1LL << b);
            }

            cnt += x_mul_in_range(l, r);
        
            if (!((x >> b) & 1)) {
                acc |= (1LL << b);
            }
        } else if ((x >> b) & 1) {
            acc |= (1LL << b);
        }
    }
    cnt += (acc % x == 0) && (acc != x);

    for (i64 y = 1; y <= min(m, 2 * x); y++) {
        if (y == x) continue;

        i64 res = x ^ y;
        if (res % y == 0 && res % x != 0) {
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
