#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int s; cin >> s;
    s--;

    vector<int> al(a.begin(), a.begin() + s + 1);
    vector<int> ar(a.begin() + s, a.end());
    reverse(ar.begin(), ar.end());

    al.resize(unique(al.begin(), al.end()) - al.begin());
    ar.resize(unique(ar.begin(), ar.end()) - ar.begin());

    if (!al.empty() && al.front() == a[s]) al.erase(al.begin());
    if (!ar.empty() && ar.front() == a[s]) ar.erase(ar.begin());

    int ans = max(al.size(), ar.size());
    if (ans % 2) ans++;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
