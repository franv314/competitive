#include <bits/stdc++.h>
using namespace std;

void solve() {
    int m; cin >> m;

    long long sum_l = 0, sum_r = 0, tot = 0;
    int sum_n = 0;

    vector<pair<long long, long long>> range(m);
    vector<long long> total(m);
    map<long long, vector<pair<int, long long>>> numbers;

    for (int i = 0; i < m; i++) {
        int n; cin >> n;
        sum_n += n;

        long long l, r; cin >> l >> r;
        range[i] = {l, r};
        sum_l += l, sum_r += r;

        vector<long long> a(n), f(n);
        for (auto &x: a) cin >> x;
        for (auto &x: f) {
            cin >> x;
            tot += x;
            total[i] += x;
        }

        for (int j = 0; j < n; j++) numbers[a[j]].emplace_back(i, f[j]);
    }

    long long megatotalone = 0;
    for (auto [l, r]: range) megatotalone += r;

    if (sum_r - sum_l + 1 > sum_n) return void(cout << "0\n");

    long long mi = LLONG_MAX;

    for (long long x = sum_l; x <= sum_r; x++) {
        long long ans = 0;
        long long taken = megatotalone;
        for (auto [s, cnt]: numbers[x]) {
            auto [l, r] = range[s];
            taken -= r;
            if (cnt > total[s] - l) {
                ans += cnt - (total[s] - l);
                taken += l;
            } else {
                taken += min(r, total[s] - cnt);
            }
        }

        if (taken < x) {
            ans += x - taken;
        }
        mi = min(mi, ans);
    }

    cout << mi << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}