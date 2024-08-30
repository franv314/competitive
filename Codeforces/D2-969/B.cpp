#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    long long w; cin >> w;
    vector<int> p(n);
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        adj[--p[i]].push_back(i);
    }

    for (auto &x: adj) sort(x.begin(), x.end());

    vector<array<int, 2>> interested(n);
    vector<int> cnt(n);

    auto dfs = [&](auto &&dfs, int node, int last = -1) -> int {
        int ma = node;
        int l = node;

        for (auto x: adj[node]) {
            int ch = max(ma, dfs(dfs, x, l));
            ma = max(ma, ch);
            l = ch;
        }
        
        if (node) {
            interested[node] = {last, ma};
            cnt[last]++;
            cnt[ma]++;
        }
        return ma;
    };

    dfs(dfs, 0);
    vector<long long> sum(n);
    long long revealed = 0;
    long long ans = n * w;
    int unsat = n;

    auto get_ans = [&](int node) {
        if (cnt[node] == 0) return sum[node];
        long long other = revealed - sum[node];
        return w - other;
    };

    for (int _ = 0; _ < n - 1; _++) {
        int x; cin >> x;
        long long y; cin >> y;
        x--;

        for (auto z: interested[x]) {
            long long old = get_ans(z);
            sum[z] += y;
            if (--cnt[z] == 0) unsat--;
            revealed += y;
            ans += get_ans(z) - old;

            revealed -= y;
        }
        revealed += y;
    
        int sus = unsat;
        for (auto z: interested[x])
            sus -= cnt[z] != 0;

        ans -= sus * y;

        cout << ans << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}