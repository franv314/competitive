#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<int>> pos(26, vector<int>());
    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].push_back(i); 
    }

    int curr = -1;
    vector<int> subs(n, -1);
    vector<int> decr;
    int fst = -1;
    for (int i = 25; i >= 0; i--) {
        if (fst == -1 && !pos[i].empty()) {
            fst = pos[i].size();
        }
        for (auto p: pos[i]) {
            if (p <= curr) continue;
            decr.push_back(p);
            subs[p] = decr.size() - 1;
            curr = p;
        }
    }

    reverse(decr.begin(), decr.end());

    string t = s;
    for (int i = 0; i < n; i++) {
        if (subs[i] != -1) {
            t[i] = s[decr[subs[i]]];
        }
    }

    if (is_sorted(t.begin(), t.end())) {
        int ans = decr.size();
        
        cout << ans - fst << '\n';
    } else {
        cout << -1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}