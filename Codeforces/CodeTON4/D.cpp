#include <bits/stdc++.h>
using namespace std;

void solve() {
    int q; cin >> q;
    long long mi = 1, ma = LLONG_MAX;

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            long long a, b, n; cin >> a >> b >> n;

            long long lo = (n - 1) * a - (n - 2) * b + 1;
            long long hi = n * a - (n - 1) * b;

            if (n == 1) {
                lo = 1;
                hi = a;
            }

            if (lo > ma || hi < mi) {
                cout << "0 ";
                continue;
            }
            
            cout << "1 ";
            mi = max(mi, lo);
            ma = min(ma, hi);
        } else {
            int a, b; cin >> a >> b;
            
            long long days_for_ma, days_for_mi;
            if (ma <= a) days_for_ma = 1;
            else days_for_ma = (ma - a - 1) / (a - b) + 2;

            if (mi <= a) days_for_mi = 1;
            else days_for_mi = (mi - a - 1) / (a - b) + 2;

            if (days_for_mi == days_for_ma) cout << days_for_mi << " ";
            else cout << "-1 ";
        }
    }
    cout << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}