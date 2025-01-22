#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &row: a)
        for (auto &el: row)
            cin >> el;

    for (auto &row: a)
        sort(row.begin(), row.end());

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int u, int v) { return a[u][0] < a[v][0]; });
    

    vector<vector<int>> transpose(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            transpose[j][i] = a[order[i]][j];

    for (int i = 0; i < m - 1; i++)
        if (transpose[i + 1][0] < transpose[i][n - 1])
            return void(cout << "-1\n");

    for (auto &row: transpose)
        if (!is_sorted(row.begin(), row.end()))
            return void(cout << "-1\n");
    
    for (auto x: order)
        cout << x + 1 << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
