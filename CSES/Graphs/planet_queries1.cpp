#include <bits/stdc++.h>
using namespace std;

#define LOG 30

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<vector<int>> nxt(LOG, vector<int>(n));

    for (auto &x: nxt[0]) {
        cin >> x;
        x--;
    }

    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < n; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }

    while (q--) {
        int x, k; cin >> x >> k;
        x--;

        for (int i = 0; i < LOG; i++) {
            if ((k >> i) & 1) x = nxt[i][x];
        }

        cout << x + 1 << '\n';
    }
}