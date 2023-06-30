#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int m; cin >> m;
        vector<vector<int>> users(m);
        vector<int> ans(m, -1);
        set<int> players;

        for (auto &v: users) {
            int n; cin >> n;
            v.resize(n);
            for (auto &u: v) cin >> u;
        }
        
        for (int k = m - 1; k >= 0; k--) {
            for (auto user: users[k]) {
                if (players.find(user) == players.end()) {
                    ans[k] = user;
                }
                players.insert(user);
            }
            if (ans[k] == -1) {
                cout << "-1\n";
                goto next;
            }
        }

        for (auto x: ans) cout << x << " "; cout << "\n";
        next:;
    }
}