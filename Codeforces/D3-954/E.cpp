#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, vector<int>> equiv;
    for (auto x: a) equiv[x % k].push_back(x);

    int odds = 0;
    long long ans = 0;
    for (auto &[_, x]: equiv) {
        sort(x.begin(), x.end());
        if (x.size() & 1) {
            odds++;
            vector<long long> ps(x.size() + 1);
            for (int i = 0; i < x.size(); i++) {
                if (i & 1)
                    ps[i + 1] = ps[i] + x[i];
                else
                    ps[i + 1] = ps[i] - x[i];
            }
            long long mi = 1e18;
            for (int out = 0; out < x.size(); out++) {
                mi = min(mi, (ps[out] - ps[0]) - (ps[x.size()] - ps[out + 1]));
            }
            ans += mi / k;
        } else {
            for (int i = 0; i < x.size(); i += 2)
                ans += (x[i + 1] - x[i]) / k;
        }
    }

    if (odds > (n & 1)) cout << "-1\n";
    else cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}