#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);

    for (auto &x: a) cin >> x;

    int mi = *min_element(a.begin(), a.end());
    int ma = *max_element(a.begin(), a.end());

    if (mi == ma) return void(cout << 0 << '\n');

    int k = 1 + (int)log2(ma - mi);

    cout << k << '\n';
    if (k > n) return;

    while (mi != ma) {
        if (mi & 1) {
            mi++;
            ma++;
            cout << 1 << ' ';
        } else {
            cout << 0 << ' ';
        }
        mi /= 2;
        ma /= 2;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}