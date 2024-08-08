#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> cnt(2 * k);
    int fc = -1e9;
    for (auto x: a) {
        if (x % (2 * k) < k) {
            cnt[x % (2 * k)]++;
            cnt[(x + k) % (2 * k)]--;
        } else {
            cnt[x % (2 * k)]++;
            cnt[(x + k) % (2 * k)]--;
            cnt[0]++;
        }

        fc = max(fc, x / (2 * k));
    }

    for (int i = 1; i < 2 * k; i++)
        cnt[i] += cnt[i - 1];
    
    int ma = *max_element(a.begin(), a.end());
    for (int i = ma; i < ma + 2 * k; i++) {
        if (cnt[i % (2 * k)] == n) {
            cout << i << '\n';
            return;
        }
    }

    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}