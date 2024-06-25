#include <bits/stdc++.h>
using namespace std;

int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i++) {
        bool found = false;
        while (n % i == 0) {
            n /= i;
            found = true;
        }
        
        if (found)
            ans = ans / i * (i - 1);
    }
    
    if (n != 1)
        ans = ans / n * (n - 1);
    
    return ans;
}

int fexp(int base, int exp, int mod) {
    int ans = 1;
    do {
        if (exp & 1) ans = (long long)ans * base % mod;
        base = (long long)base * base % mod;
    } while (exp >>= 1);
    return ans;
}

void solve() {
    int n, m, h; cin >> n >> m >> h;
    vector<int> l(n), s(n);
    for (auto &x: l) cin >> x;
    for (auto &x: s) cin >> x;
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    
    int p = phi(h);
    
    auto first_time = [&](int l0, int s0, int l1, int s1, long long curr) -> long long {
        int lhs = (l0 - l1 + h) % h;
        int rhs = (s1 - s0 + h) % h;
        
        int gl = gcd(lhs, h);
        int gr = gcd(rhs, h);
        
        if (gl % gr) return -1;
        
        int H = h / gr;
        rhs /= gr;
        lhs /= gr;
        
        int k = (long long)lhs * fexp(rhs, p - 1, H) % H;
        
        int diff = (k - curr % H + H) % H;

        return curr + diff;
    };
    
    vector<long long> dst(n, 1e18);
    vector<bool> visited(n, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    
    q.emplace(dst[0] = 0, 0);
    
    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (visited[n]) continue;
        visited[n] = true;
        
        for (auto x: adj[n]) {
            long long t = first_time(l[n], s[n], l[x], s[x], d);
            if (t != -1 && t + 1 < dst[x]) {
                q.emplace(dst[x] = t + 1, x);
            }
        }
    }
    
    if (dst[n - 1] == 1e18) cout << -1 << '\n';
    else cout << dst[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}