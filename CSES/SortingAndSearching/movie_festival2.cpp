#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> events(n);

    for (auto &[b, a]: events) cin >> a >> b;

    multiset<int> free_at;
    for (int i = 0; i < k; i++) free_at.insert(0);

    sort(events.begin(), events.end());

    int ans = 0;
    for (auto [b, a]: events) {
        if (*free_at.begin() > a) continue;
        ans++;
        free_at.erase(prev(free_at.upper_bound(a)));
        free_at.insert(b);
    }

    cout << ans << '\n';
}