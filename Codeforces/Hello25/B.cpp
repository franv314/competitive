#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, int> freq;
    for (auto x: a) freq[x]++;

    vector<int> f;
    for (auto [_, ff]: freq) f.push_back(ff);

    sort(f.begin(), f.end());
    int ans = f.size();

    for (int i = 0; i < f.size(); i++) {
        if (f[i] <= k) {
            ans--;
            k -= f[i];
        }
    } 

    cout << max(1, ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
