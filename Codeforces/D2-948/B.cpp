#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> ans(31);
    
    for (int bit = 0; bit < 31; bit++) {
        ans[bit] = (n >> bit) & 1;
        if (bit > 0 && ans[bit] && ans[bit - 1]) {
            ans[bit] = 0;
            ans[bit - 1] = -1;
            n += (1 << bit);
        }
    }

    cout << 31 << '\n';
    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}