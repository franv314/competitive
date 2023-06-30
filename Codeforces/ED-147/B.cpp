#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);

    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    int l = -1, r;

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            if (l == -1) l = i;
            r = i;
        }
    }
    while (l && b[l] >= b[l - 1]) l--;
    while (r < n - 1 && b[r] <= b[r + 1]) r++;
    cout << l + 1 << " " << r + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}