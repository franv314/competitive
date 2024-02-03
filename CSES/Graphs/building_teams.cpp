#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    vector<int> team(n);

    function<bool(int, int, int)> dfs = [&](int node, int par, int col) {
        team[node] = col;

        for (auto x: adj[node]) {
            if (team[x]) {
                if (team[x] == team[node]) return false;
            } else if (!dfs(x, node, col ^ 3)){
                return false;
            }
        }

        return true;
    };

    for (int i = 0; i < n; i++) {
        if (team[i]) continue;
        if (!dfs(i, -1, 1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (auto x: team) cout << x << ' ';
    cout << '\n';
}