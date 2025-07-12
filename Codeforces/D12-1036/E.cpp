#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    i64 n; cin >> n;
    vector<i64> a(n);
    for (auto &x: a) cin >> x;

    i64 total = accumulate(a.begin(), a.end(), 0LL);
    i64 max = *max_element(a.begin(), a.end());

    if (2 * max > total || total % 2) return void(cout << "-1\n");

    i64 ps = 0;
    for (auto x: a) {
        ps += x;
        if (2 * ps == total) {
            cout << "1\n";
            for (auto x: a) cout << x << " ";
            cout << "\n";
            return;
        }
    }

    i64 cutoff;
    i64 l = 0, h;
    for (cutoff = 0; cutoff < n; cutoff++) {
        if (l + a[cutoff] >= total / 2) {
            h = a[cutoff];
            break;
        }
        l += a[cutoff];
    }

    i64 r = total - l - h;

    i64 c = (l + r - h) / 2;
    i64 hl = l - c;
    i64 hr = r - c;

    assert(c >= 0 && hl >= 0 && hr >= 0);

    cout << "2\n";

    for (i64 i = 0; i < cutoff; i++) {
        cout << a[i] << " ";
    }
    cout << hl << " ";
    for (i64 i = cutoff + 1; i < n; i++) {
        i64 rem = min(c, a[i]);
        cout << rem << " ";
        c -= rem;
        a[i] -= rem;
    }
    cout << "\n";

    for (i64 i = 0; i < cutoff; i++) {
        cout << 0 << " ";
    }
    cout << hr << " ";
    for (i64 i = cutoff + 1; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    i64 t; cin >> t;
    while (t--) solve();
}
