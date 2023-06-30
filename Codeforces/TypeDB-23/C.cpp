#include <bits/stdc++.h>
using namespace std;

long long solve_tc() {
    int n, s; cin >> n >> s;
    vector<long long> a(n), x(n), y(n);
    for (auto &x: a) cin >> x;
    
    long long z = LLONG_MAX;
    for (int pos = 0; pos < n; pos++) {
        for (int i = 0; i < n; i++) {
            if (a[i] > s) {
                x[i] = s;
                y[i] = a[i] - s;
            } else {
                x[i] = 1;
                y[i] = a[i] - 1;
            }

            if (x[i] > y[i]) swap(x[i], y[i]);
            if (i > pos) swap(x[i], y[i]);
        }

        long long ans = 0;
        for (int i = 1; i < n - 2; i++) {
            ans += y[i] * x[i + 1];
        }
        ans += a[0] * x[1];
        ans += y[n - 2] * a[n - 1];
        cout << pos << " " << ans << endl;
        z = min(z, ans);
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cout << solve_tc() << "\n";
    }
}