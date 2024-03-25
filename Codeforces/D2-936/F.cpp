#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000

struct Fenwick {
    vector<long long> arr;

    void update(int x, int d) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += d;
    }

    long long query(int x) {
        long long ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    Fenwick(int N) : arr(N + 1) { }
};

vector<vector<int>> divs;

void precalc() {
    divs.resize(MAXN + 1);
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 2 * i; j <= MAXN; j += i) {
            divs[j].push_back(i);
        }
    }
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<pair<int, int>>> queries(n);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[l - 1].emplace_back(r, i);
    }

    vector<long long> ans(q);
    vector<int> pos_of(n + 1);
    for (int i = 0; i < n; i++) pos_of[a[i]] = i;

    vector<long long> dp(n);
    Fenwick fenwick(n);

    auto update = [&](int x) -> long long {
        long long ans = 1;
        for (auto div: divs[x])
            if (pos_of[div] < pos_of[x])
                ans += dp[pos_of[div]];
        return ans;
    };

    for (int i = 0; i < n; i++) {
        dp[i] = update(a[i]);
        fenwick.update(i + 1, dp[i]);
    }

    for (int l = 0; l < n; l++) {
        for (auto [r, idx]: queries[l])
            ans[idx] = fenwick.query(r);
        
        fenwick.update(l + 1, -dp[l]);
        dp[l] = 0;

        for (int x = a[l]; x <= n; x += a[l]) {
            if (pos_of[x] <= l) continue;

            long long old = dp[pos_of[x]];
            dp[pos_of[x]] = update(x);
            fenwick.update(pos_of[x] + 1, dp[pos_of[x]] - old);
        }
    }

    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    precalc();

    int t; cin >> t;
    while (t--) solve();
}