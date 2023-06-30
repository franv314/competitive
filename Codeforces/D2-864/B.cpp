#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        
        vector<vector<int>> g(n, vector<int>(n));
        for (auto &x: g) {
            for (auto &c: x) {
                cin >> c;
            }
        }

        int inv = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inv += g[i][j] != g[n - i - 1][n - j - 1];
            }
        }

        inv /= 2;

        if (n & 1) {
            if (k >= inv) cout << "YES\n";
            else cout << "NO\n";
        } else {
            if (k >= inv && (inv & 1) == (k & 1)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}