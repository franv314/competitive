#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    if (k == 2 || k == 3 || k == 5) {
        int mi = 1000;
        for (auto x: a) {
            mi = min(mi, (k - (x % k)) % k);
        }
        cout << mi << '\n';
    } else {
        int mi = 1000;
        for (auto x: a) {
            mi = min(mi, (k - (x % k)) % k);
        }
        
        int odd = 0, even = 0;
        for (auto x: a) {
            odd += (x & 1);
            even += !(x & 1);
        }

        if (even >= 2) mi = min(mi, 0);
        else if (even == 1 && odd >= 1) mi = min(mi, 1);
        else if (even == 0 && odd >= 2) mi = min(mi, 2);

        cout << mi << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}