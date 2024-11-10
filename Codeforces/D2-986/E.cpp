#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

constexpr i64 MOD = 998244353;

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<pair<int, int>> dp(n, {1e9, -1});

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> void {
        for (auto ch: adj[node]) {
            if (ch == par) continue;

            dfs(dfs, ch, node, d + 1);
            dp[node] = min(dp[node], {dp[ch].first, ch});
        }

        if (dp[node].first == 1e9) {
            dp[node] = {d, node};
        }
    };

    dfs(dfs, 0);
    vector<i64> ans(n);

    auto chains = [&](auto &&chains, int node, int par = -1) -> void {
        vector<int> chain = {node};
        while (dp[chain.back()].second != chain.back()) {
            chain.push_back(dp[chain.back()].second);
        }
        
        int l = chain.size();
        for (int i = 0; i < l; i++) {
            i64 k = l - 1 - i;
            i64 p = k * fexp(l - 1 + (par != -1), MOD - 2) % MOD;

            if (par != -1)
                p = p * ans[par] % MOD;
            
            ans[chain[i]] = p;
        }
        
        for (int i = 0; i < chain.size(); i++) {
            for (auto ch: adj[chain[i]]) {
                bool ok = ch != par;
                if (i > 0)
                    ok &= chain[i - 1] != ch;
                if (i < chain.size() - 1)
                    ok &= chain[i + 1] != ch;
                
                if (!ok)
                    continue;

                chains(chains, ch, chain[i]);
            }
        }
    };

    chains(chains, 0);

    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
