#include <bits/stdc++.h>
using namespace std;

enum dir_t { HOR = 1, VER };

unsigned char *dp;

void solve() {
    int n, m; cin >> n >> m;
    int r; cin >> r;
    map<int, set<pair<int, dir_t>>> shots;
    for (int i = 0; i < r; i++) {
        int t, d, coord; cin >> t >> d >> coord;
        shots[t].insert({coord, (dir_t)d});
    }
    
    int S1 = n + 1;
    int S2 = m + 1;
    
    auto get_dp = [&](int x, int y, int z) -> unsigned char& {
        return dp[x + y * S1 + z * S1 * S2];
    };          
                
    for (int t = 0; t < n + m + r + 10; t++) get_dp(n, m, t) = 0;
    
    for (int t = n + m + r + 8; t >= 0; t--) {
        for (int x = 0; x <= n; x++) {
            for (int y = 0; y <= m; y++) {
                if (x == n && y == m) continue;
                get_dp(x, y, t) = 101;
                if (!shots[t + 1].count({x, HOR}) && !shots[t + 1].count({y, VER}))
                    get_dp(x, y, t) = 1 + get_dp(x, y, t + 1);
                if (x != n && !shots[t + 1].count({x + 1, HOR}) && !shots[t + 1].count({y, VER})) {
                    get_dp(x, y, t) = min(get_dp(x, y, t), get_dp(x + 1, y, t + 1));
                }
                if (y != m && !shots[t + 1].count({x, HOR}) && !shots[t + 1].count({y + 1, VER})) {
                    get_dp(x, y, t) = min(get_dp(x, y, t), get_dp(x, y + 1, t + 1));
                }
            }
        }
    }
    if (get_dp(0, 0, 0) >= 101) cout << "-1\n";
    else cout << n + m + get_dp(0, 0, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    dp = (unsigned char*)malloc(210'000'000);
    int t; cin >> t;
    while (t--) solve();
}