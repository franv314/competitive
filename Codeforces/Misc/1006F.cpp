#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    long long k; cin >> k;
    int len = (n + m - 1) / 2;
    
    vector grid(n, vector(m, 0ll));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    vector<unordered_map<long long, long long>> cnt(n);
    function<void(int, int, long long)> dfs1 = [&](int i, int j, long long x) {
        if (i + j == len)
            return void(cnt[i][x]++);
        
        if (i + 1 < n)
            dfs1(i + 1, j, x ^ grid[i + 1][j]);
        if (j + 1 < m)
            dfs1(i, j + 1, x ^ grid[i][j + 1]);
    };
    
    function<long long(int, int, long long)> dfs2 = [&](int i, int j, long long x) {
        if (i + j == len)
            return cnt[i][k ^ x];
        
        long long ans = 0;
        if (i > 0)
            ans += dfs2(i - 1, j, x ^ grid[i][j]);
        if (j > 0)
            ans += dfs2(i, j - 1, x ^ grid[i][j]);
        return ans;
    };
    
    dfs1(0, 0, grid[0][0]);
    cout << dfs2(n - 1, m - 1, 0);
}