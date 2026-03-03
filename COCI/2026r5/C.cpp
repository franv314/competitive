#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2000;

#define int __int128_t

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
 
    signed _n, _m; cin >> _n >> _m;

    int n = _n, m = _m;
    vector<bitset<MAXN>> grid(n);
    for (auto &row: grid)
        cin >> row;

    vector<int> rows(n), cols(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rows[i] += grid[i][j];
            cols[j] += grid[i][j];
        }
    }

    vector<vector<int>> row_paths(n, vector<int>(m));
    vector<vector<int>> col_paths(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                cnt += cols[j] - 1;
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                row_paths[i][j] = cnt - cols[j] + 1;
    }

    for (int j = 0; j < m; j++) {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (grid[i][j])
                cnt += rows[i] - 1;
        for (int i = 0; i < n; i++)
            if (grid[i][j])
                col_paths[i][j] = cnt - rows[i] + 1;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cnt += 2LL * row_paths[i][j] * col_paths[i][j];
        }
    }

    int squares = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int shared = (grid[i] & grid[j]).count();
            if (shared == 0) continue;
            squares += shared * (shared - 1) / 2;
        }
    }

    int ans = cnt - 8 * squares;
    string ret;
    while (ans) {
        ret += '0' + ans % 10;
        ans /= 10;
    }
    reverse(ret.begin(), ret.end());
    if (ret == "") ret = "0";
    cout << ret << "\r\n";
}
