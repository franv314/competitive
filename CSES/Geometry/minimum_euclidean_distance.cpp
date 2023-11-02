#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<pair<int, int>> points(n);
    for (auto &[x, y]: points) cin >> x >> y;

    sort(points.begin(), points.end());
    long long best = LLONG_MAX;

    set<pair<int, int>> s;
    int removed = 0;

    for (auto [px, py]: points) {
        while ((long long)(points[removed].first - px) * (points[removed].first - px) > best) {
            s.erase({points[removed].second, points[removed].first});
            removed++;
        }

        for (
            auto it = s.lower_bound({py - sqrtl(best), INT_MIN});
            it != s.end() && it->first <= py + sqrtl(best);
            it++
        ) {
            best = min(
                best,
                (long long)(px - it->second) * (px - it->second) + (long long)(py - it->first) * (py - it->first)
            );
        }

        s.emplace(py, px);
    }

    cout << best << '\n';
}