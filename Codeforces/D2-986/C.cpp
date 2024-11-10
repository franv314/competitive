#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, v; cin >> n >> m >> v;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<long long> ps(n + 1);
    for (int i = 0; i < n; i++)
        ps[i + 1] = ps[i] + a[i];

    vector<int> pref_take(m + 1, - 1), suff_take(m + 1, - 1);

    pref_take[0] = 0;
    int curr = 0;
    for (int i = 0; i < n && curr < m; i++) {
        if (ps[i + 1] - ps[pref_take[curr]] >= v) {
            pref_take[++curr] = i + 1;
        }
    }

    suff_take[0] = n;
    curr = 0;
    for (int i = n - 1; i >= 0 && curr < m; i--) {
        if (ps[suff_take[curr]] - ps[i] >= v) {
            suff_take[++curr] = i;
        }
    }

    if (pref_take[m] == -1)
        return void(cout << "-1\n");
    
    long long ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, ps[suff_take[i]] - ps[pref_take[m - i]]);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
