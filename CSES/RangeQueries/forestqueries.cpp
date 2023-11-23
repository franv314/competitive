#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<vector<int>> ps(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) {
            int v = s[j - 1] == '*';
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + v;
        }
    }

    while (q--) {
        int i1, j1, i2, j2; cin >> i1 >> j1 >> i2 >> j2;
        cout << ps[i2][j2] - ps[i1 - 1][j2] - ps[i2][j1 - 1] + ps[i1 - 1][j1 - 1] << '\n';
    }
}