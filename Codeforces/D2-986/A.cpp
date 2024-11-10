#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;

    vector<pair<int, int>> ps(n + 1);
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1];
        switch (s[i - 1]) {
        case 'N': ps[i].second++; break;
        case 'S': ps[i].second--; break;
        case 'E': ps[i].first++; break;
        case 'W': ps[i].first--; break;
        }
    }

    for (int i = 0; i < n; i++) {
        int dx = a - ps[i].first;
        int dy = b - ps[i].second;

        if (dx * ps[n].first < 0) continue;
        if (dy * ps[n].second < 0) continue;

        if (ps[n].first && dx % ps[n].first) continue;
        if (ps[n].second && dy % ps[n].second) continue;

        if (ps[n].first == 0 && dx != 0) continue;
        if (ps[n].second == 0 && dy != 0) continue;

        if (ps[n].first != 0 && ps[n].second != 0 && (dx / ps[n].first != dy / ps[n].second)) continue;

        return void(cout << "YES\n");
    }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
