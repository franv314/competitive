#include <bits/stdc++.h>
using namespace std;

#define BITS 20

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;

        array<int, BITS> cnt = {};
        for (int i = 0; i < m; i++) {
            for (int b = 0; b < BITS; b++) {
                cnt[b] += (a[i] >> b) & 1;
            }
        }

        bool ok = true;
        array<int, BITS> fst = cnt;

        for (int i = m; i < n; i++) {
            for (int b = 0; b < BITS; b++) {
                cnt[b] += (a[i] >> b) & 1;
                cnt[b] -= (a[i - m] >> b) & 1;
            }

            for (int b = 0; b < BITS; b++) {
                if ((cnt[b] != 0) != (fst[b] != 0)) {
                    ok = false;
                }
            }
        }

        if (ok) r = m;
        else l = m;
    }

    cout << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}