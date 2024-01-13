#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> bad;
    int mi = -1e9, ma = 1e9;

    while (n--) {
        int a, x; cin >> a >> x;
        if (a == 1) mi = max(mi, x);
        if (a == 2) ma = min(ma, x);
        if (a == 3) bad.insert(x);
    }

    int z = 0;
    for (auto x: bad) {
        if (x > ma || x < mi) z++;
    }

    if (ma < mi) cout << 0 << '\n';
    else cout << ma - mi + 1 - (int)bad.size() + z << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}