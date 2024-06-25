#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y, k; cin >> x >> y >> k;

    while (x > 1) {
        int add = y - x % y;
        if (add > k) {
            x += k;
            k = 0;
            break;
        }
        k -= add;
        x += add;
        while (x % y == 0)
            x /= y;
    }

    x += k % (y - 1);

    cout << x << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}