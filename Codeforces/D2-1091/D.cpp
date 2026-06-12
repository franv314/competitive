#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n), s(k);
    for (auto &x: a) cin >> x;
    for (auto &x: s) {
        cin >> x;
        x--;
    }

    vector<vector<int>> segments;
    segments.emplace_back(a.begin(), a.begin() + s[0] + 1);

    for (int i = 0; i < k - 1; i++) {
        segments.emplace_back(a.begin() + s[i], a.begin() + s[i + 1] + 1);
    }

    segments.emplace_back(a.begin() + s.back(), a.end());

    for (auto &seg: segments) {
        seg.resize(unique(seg.begin(), seg.end()) - seg.begin());
    }

    if (segments[0][0] == a[s[0]]) segments[0].erase(segments[0].begin());

    for (int i = 1; i < segments.size(); i++)
        if (segments[i].back() == a[s[0]])
            segments[i].pop_back();
    
    int sum = 0, ma = 0;
    for (auto seg: segments) {
        sum += seg.size();
        ma = max(ma, (int)seg.size());
    }

    int ans = max(ma, (sum + 1) / 2);
    if (k == 1 && ans % 2) ans++;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
