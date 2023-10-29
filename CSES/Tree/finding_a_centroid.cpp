#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);

    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> sizes(n);

    function<int(int, int)> dfs = [&](int node, int par) {
        sizes[node] = 1;
        for (auto c: adj[node]) {
            if (c == par) continue;
            sizes[node] += dfs(c, node);
        }
        return sizes[node];
    };

    dfs(0, -1);

    bool done;
    int centroid = 0;
    do {
        done = true;
        for (auto x: adj[centroid]) {
            if (sizes[x] < sizes[centroid] && 2 * sizes[x] > n) {
                centroid = x;
                done = false;
                break;
            }
        }
    } while (!done);

    cout << 1 + centroid << '\n';
}