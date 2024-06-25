#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y, z; cin >> x >> y >> z;
    long long k; cin >> k;

    long long ma = 0;

    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            if (k % (i * j)) continue;
            long long l = k / (i * j);
            if (l > z) continue;

            ma = max(ma, (long long)(x - i + 1) * (y - j + 1) * (z - l + 1));
        }
    }

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}