#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> ans(n);

    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[p - 1].push_back(i);
    }

    function<int(int)> dfs = [&](int node) {
        ans[node] = 0;
        
        for (auto c: adj[node]) {
            ans[node] += dfs(c);
        }

        return ans[node] + 1;
    };

    dfs(0);

    for (auto x: ans) cout << x << ' ';
}