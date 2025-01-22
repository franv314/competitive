#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<pair<int, int>> ranges_a, ranges_b; 
    for (int i = 0; i < n / 2; i++) {
        ranges_a.emplace_back(a[n - 1 - i] - a[i], 0);
    }
    for (int i = 0; i < m / 2; i++) {
        ranges_b.emplace_back(b[m - 1 - i] - b[i], 1);
    }

    vector<pair<int, int>> ranges;
    merge(ranges_a.begin(), ranges_a.end(), ranges_b.begin(), ranges_b.end(), back_inserter(ranges), greater());

    vector<i64> ps_a = {0}, ps_b = {0}, ps = {0};
    vector<int> ps_ta = {0}, ps_tb = {0};

    for (auto [l, _]: ranges_a)
        ps_a.push_back(ps_a.back() + l);
    for (auto [l, _]: ranges_b)
        ps_b.push_back(ps_b.back() + l);

    for (auto [l, t]: ranges) {
        ps.push_back(ps.back() + l);

        ps_ta.push_back(ps_ta.back() + (t == 0));
        ps_tb.push_back(ps_tb.back() + (t == 1));
    }

    auto get_max = [&](int n, int m) -> int {
        return (n <= 2 * m && m <= 2 * n) ? (n + m) / 3 : min(n, m);
    };

    auto check = [&](int pf, int k) -> bool {
        int rem_a = n - 2 * ps_ta[pf] - ps_tb[pf];
        int rem_b = m - 2 * ps_tb[pf] - ps_ta[pf];

        if (rem_a < 0 || rem_b < 0)
            return false;

        int total = pf + get_max(rem_a, rem_b);
        return total >= k;
    };

    int kmax = get_max(n, m);
    cout << kmax << '\n';

    for (int i = 1; i <= kmax; i++) {
        int l = 0, r = i + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            
            if (check(m, i))
                l = m;
            else
                r = m;
        }

        i64 ans = ps[l];
        if (l == ps.size() - 1) {
            cout << ans << ' ';
            continue;
        }

        if (ps_ta[l + 1] == ps_ta[l]) {
            ans += ps_a[ps_ta[l] + i - l] - ps_a[ps_ta[l]];
        } else {
            ans += ps_b[ps_tb[l] + i - l] - ps_b[ps_tb[l]];
        }

        cout << ans << ' ';
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
