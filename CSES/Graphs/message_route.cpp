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

    vector<int> origin(n, -1);
    
    queue<pair<int, int>> q;
    q.emplace(0, -2);

    while (!q.empty()) {
        auto [node, orig] = q.front(); q.pop();
        
        if (origin[node] != -1) continue;
        origin[node] = orig;
    
        for (auto x: adj[node]) q.emplace(x, node);
    }

    if (origin[n - 1] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans;
    for (int node = n - 1; node != -2; node = origin[node]) {
        ans.push_back(node);
    }

    cout << ans.size() << '\n';
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
}