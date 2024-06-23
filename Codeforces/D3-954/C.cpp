#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<int> ind(m);
    for (auto &x: ind) cin >> x;
    string t; cin >> t;

    sort(ind.begin(), ind.end());
    ind.resize(unique(ind.begin(), ind.end()) - ind.begin());
    sort(t.begin(), t.end());

    for (int i = 0; i < ind.size(); i++) {
        s[ind[i] - 1] = t[i];
    }

    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}