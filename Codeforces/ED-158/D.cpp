#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int l = 0, r = 1.05e9;
    while (l + 1 < r) {
        int m = (l + r) / 2;

        bool ok = true;

        int R = n - 1, L = 0;
        int force = -1;

        for (int i = 0; i < n; i++) {
            int ok_drop = m - a[i];
            if (ok_drop < 0) {
                ok = false;
                break;
            }

            if (ok_drop >= i && ok_drop >= n - 1 - i) {
            } else if (ok_drop >= i) {
                R = min(R, i);
            } else if (ok_drop >= n - 1 - i) {
                L = max(L, i);
            } else {
                if (force != -1) {
                    ok = false;
                    break;
                } else {
                    force = i;
                }
            }
        }

        ok &= (R >= L);
        ok &= (force == -1 || (L <= force && force <= R));

        if (ok) r = m;
        else l = m;
    }

    cout << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}