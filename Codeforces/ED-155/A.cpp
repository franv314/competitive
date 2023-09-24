#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<tuple<int, int, int>> athletes;
    
    for (int i = 0; i < n; i++) {
        int s, e; cin >> s >> e;
        athletes.emplace_back(s, i, e);
    }
    
    sort(athletes.rbegin(), athletes.rend());
    int ss, ee;
    int best_e = -1;
    for (auto [s, i, e]: athletes) {
        if (i == 0) {
            ss = s;
            ee = e;
            break;
        }
        best_e = max(best_e, e);
    }
    
    if (best_e >= ee) {
        cout << -1 << '\n';
    } else {
        cout << ss << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}