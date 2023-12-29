#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> ps(n + 1);
    for (int i = 0; i < n; i++) ps[i + 1] = (ps[i] + a[i] + 1'000'000'000LL * n) % n;

    vector<int> cnt(n);
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        cnt[ps[i + 1]]++;
        ans += cnt[ps[i]];
    }

    cout << ans << '\n';
}