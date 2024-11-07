#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        int x; cin >> x;
        cnt += x;
    }

    int mi = cnt % 2;
    int ma = cnt <= n ? cnt : 2 * n - cnt;

    cout << mi << " " << ma << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
