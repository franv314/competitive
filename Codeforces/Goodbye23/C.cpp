#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long ps = 0;
    int odd = 0;
    for (int i = 0; i < n; i++) {
        ps += a[i];
        odd += a[i] & 1;
        if (i == 0) cout << ps << ' ';
        else {
            cout << ps - odd / 3 - (odd % 3 == 1) << ' ';
        }
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}