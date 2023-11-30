#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<unsigned>> mat(n, vector<unsigned>(n));

    for (auto &row: mat)
        for (auto &x: row)
            cin >> x;
    
    vector<unsigned> ans(n, (1 << 30) - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                ans[i] &= mat[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mat[i][j] != (ans[i] | ans[j])) {
                return void(cout << "NO\n");
            }
        }
    }

    cout << "YES\n";
    for (auto &x: ans) cout << x << ' '; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}