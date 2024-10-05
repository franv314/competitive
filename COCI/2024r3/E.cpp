#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000
constexpr int MOD = 1e9 + 7;

int coeff[MAXN + 1];

int fexp(int b, int e) {
    int ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    } 
    return ans;
}

void precalc() {
    int inv2 = fexp(2, MOD - 2);
    int curr = 1;

    for (int i = 1; i <= MAXN; i++) {
        curr = (long long)curr * inv2 % MOD;
        int inv_n = fexp(i, MOD - 2);

        coeff[i] = (1LL - curr + MOD) % MOD * inv_n % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    precalc();

    int n; cin >> n;

    vector<vector<int>> adj(n);
    vector<int> beauty(n);

    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[p].push_back(i);
    }

    for (auto &x: beauty) cin >> x;

    vector<int> sum(n), dp(n);
    vector<int> ans(n);

    function<void(int)> dfs_1 = [&](int node) {
        for (auto c: adj[node]) {
            dfs_1(c);
            sum[node] = (sum[node] + dp[c]) % MOD;
        }

        dp[node] = ((long long)sum[node] * coeff[adj[node].size()] + beauty[node]) % MOD;
    };

    function<void(int, int)> dfs_2 = [&](int node, int par) {
        int opsum, opdp, onsum, ondp;

        if (node != 0) {
            opsum = sum[par], opdp = dp[par], onsum = sum[node], ondp = dp[node];

            sum[par] = (sum[par] - dp[node] + MOD) % MOD;
            dp[par] = ((long long)sum[par] * coeff[adj[par].size() - (par == 0)] + beauty[par]) % MOD;

            sum[node] = (sum[node] + dp[par]) % MOD;
            dp[node] = ((long long)sum[node] * coeff[adj[node].size() + 1] + beauty[node]) % MOD;
        }

        ans[node] = dp[node];

        for (auto c: adj[node]) {
            dfs_2(c, node);
        }

        if (node != 0) {
            sum[par] = opsum, dp[par] = opdp, sum[node] = onsum, dp[node] = ondp;
        }
    };

    dfs_1(0);
    dfs_2(0, -1);

    for (auto x: ans) cout << x << '\n';
}