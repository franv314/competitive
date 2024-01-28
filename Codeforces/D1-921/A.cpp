#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, m; cin >> n >> k >> m;
    string s; cin >> s;
    
    vector<set<int>> letters(k);
    for (int i = 0; i < m; i++) {
        letters[s[i] - 'a'].insert(i);
    }
    for (auto &x: letters) x.insert(INT_MAX);

    string ans;
    int last = -1;
    bool won = false;
    for (int i = 0; i < n; i++) {
        pair<int, int> ma = {-1, -1};
        for (int j = 0; j < k; j++) {
            ma = max(ma, {*letters[j].upper_bound(last), j});
        }

        ans += ma.second + 'a';

        if (ma.first > 1e9) won = true;
        last = min(ma.first, (int)1e9);
    }

    if (won) {
        cout << "NO\n";
        cout << ans << '\n';
    } else {
        cout << "YES\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}