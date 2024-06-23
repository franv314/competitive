#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto &x: p) cin >> x;
    p.insert(p.begin(), -1);

    vector<vector<int>> divisors(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            divisors[j].push_back(i);

    vector<vector<int>> freq(n + 1);
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int g = gcd(i, p[i]);
        
        int u = p[i] / g;
        int v = i / g;

        for (auto x: divisors[u])
            freq[v].push_back(x);
    }

    for (auto &x: freq)
        sort(x.begin(), x.end());

    for (int i = 1; i <= n; i++) {
        int g = gcd(i, p[i]);
        
        int u = p[i] / g;
        int v = i / g;

        for (auto x: divisors[u])
            ans += upper_bound(freq[x].begin(), freq[x].end(), v) - lower_bound(freq[x].begin(), freq[x].end(), v);
        
        if (p[i] % i == 0)
            ans--;
    }

    cout << ans / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}