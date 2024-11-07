#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;

    vector<long long> total(k);
    for (int i = 0; i < k; i++) {
        int b, c; cin >> b >> c;
        total[b - 1] += c;
    }

    sort(total.rbegin(), total.rend());
    cout << accumulate(total.begin(), total.begin() + min(n, k), 0LL) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
