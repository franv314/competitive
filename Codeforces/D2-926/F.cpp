#include <bits/stdc++.h>
using namespace std;

#define MAXN 500'000
int fact[MAXN + 1], invf[MAXN + 1], inv[MAXN + 1];

constexpr int MOD = 998244353;

int fexp(int b, int e) {
    int a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = (long long)a * b % MOD;
        b = (long long)b * b % MOD;
    }
    return a;
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = (long long)i * fact[i - 1] % MOD;
    invf[MAXN] = fexp(fact[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--) invf[i] = (long long)(i + 1) * invf[i + 1] % MOD;
    for (int i = 1; i <= MAXN; i++) inv[i] = (long long)invf[i] * fact[i - 1] % MOD; 
}

void solve() {
    int n, C; cin >> n >> C;
    vector<array<int, 3>> tree(n);

    for (auto &[l, r, val]: tree) {
        cin >> l >> r >> val;
        l--, r--;
    }

    vector<int> dfs_order;
    
    auto dfs = [&](auto &&dfs, int node) {
        if (node == -2) return;
        dfs(dfs, tree[node][0]);
        dfs_order.push_back(tree[node][2]);
        dfs(dfs, tree[node][1]);
    };
    dfs(dfs, 0);
    dfs_order.push_back(C);

    int len = 0;
    int last = 1;

    int cnt = 1;

    for (auto x: dfs_order) {
        if (x == -1) {
            len++;
            continue;
        }

        int stars = x - last;
        int bars = len;

        int ways = 1;
        for (int i = stars + 1; i <= stars + bars; i++) ways = (long long)ways * i % MOD;
        for (int i = 1; i <= bars; i++) ways = (long long)ways * inv[i] % MOD;

        cnt = (long long)cnt * ways % MOD;

        len = 0;
        last = x;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    precalc();

    int t; cin >> t;
    while (t--) solve();
}