#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<array<int, 3>> hills(n);
    vector<pair<int, int>> starts(m);

    for (auto &[x, t, s]: hills) cin >> x >> t >> s;
    for (int i = 0; i < m; i++) {
        cin >> starts[i].first;
        starts[i].second = i;
    }

    sort(hills.begin(), hills.end());
    sort(starts.begin(), starts.end());

    set<pair<long long, int>> l, r;
    for (int i = 0; i < n; i++) {
        auto [x, t, s] = hills[i];
        r.emplace(x - t, i);
    }

    int rem = 0;

    vector<long long> ans(m);
    for (auto [a, idx]: starts) {
        while (rem < hills.size() && hills[rem][0] < a) {
            auto [x, t, s] = hills[rem];
            r.erase({x - t, rem});
            l.emplace(x + t, rem);

            rem++;
        }

        long long ma = 0;
        if (!r.empty()) {
            auto [_, i] = *r.begin();
            ma = max(ma, (long long)hills[i][1] - (hills[i][0] - a));
        }
        if (!l.empty()) {
            auto [_, i] = *l.rbegin();
            ma = max(ma, (long long)hills[i][1] - (a - hills[i][0]));
        }

        ans[idx] = ma;
    }

    for (auto x: ans) cout << x << ' '; cout << '\n';
}