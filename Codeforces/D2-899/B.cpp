#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<bitset<50>> sets(n);

    for (auto &set: sets) {
        int k; cin >> k;
        while (k--) {
            int a; cin >> a;
            set.set(a - 1);
        }
    }

    bitset<50> joined;
    for (auto &set: sets) {
        joined |= set;
    }

    int ans = 0;

    for (int i = 0; i < 50; i++) {
        if (!joined[i]) continue;
        bitset<50> joined2;
        for (auto &set: sets) {
            if (!set[i]) {
                joined2 |= set;
            }
        }
        ans = max(ans, (int)joined2.count());
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}