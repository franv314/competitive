#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define int long long

template<typename T>
using ord_tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> cities(n);
    for (auto &[x, y]: cities)
        cin >> x >> y;

    auto get_y = [&](int y, int i) {
        if (y >= 0)
            return (int)2e9 * y + i;
        return (int)2e9 * y - i;
    };

    map<int, vector<int>> cities_by_x;
    for (int i = 0; i < n; i++)
        cities_by_x[cities[i].first].push_back(get_y(cities[i].second, i));

    ord_tree<int> left, right;
    for (int i = 0; i < n; i++)
        left.insert(get_y(cities[i].second, i));

    auto check_cnt = [&](const ord_tree<int> &check, int k) -> optional<pair<int, int>> {
        if (2 * k > check.size())
            return {};
        
        int last_in_first = *check.find_by_order(k - 1) / (int)2e9;
        int first_in_second = *check.find_by_order(check.size() - k) / (int)2e9;

        return {{last_in_first, first_in_second}}; // excluded-included
    };

    auto check = [&]() -> pair<int, int> {
        int l = 0, r = n + 1;
        int solver = 0;

        while (r - l > 1) {
            int m = (l + r) / 2;

            auto range_left = check_cnt(left, m);
            auto range_right = check_cnt(right, m);

            if (!range_left || !range_right) {
                r = m;
                continue;
            }

            auto [ll, rl] = range_left.value();
            auto [lr, rr] = range_right.value();

            if (min(rl, rr) <= max(ll, lr))
                r = m;
            else {
                l = m;
                solver = min(rl, rr);
            }
        }

        return {l, solver};
    };

    array<int, 3> ans = {0, 0, 0};

    for (auto [x, ct]: cities_by_x) {
        auto [c, y] = check();
        ans = max(ans, {c, x, y});

        for (auto y: ct) {
            right.insert(y);
            left.erase(y);
        }
    }

    cout << ans[0] << "\n" << ans[1] << " " << ans[2] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
