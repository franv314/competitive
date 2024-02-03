#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<vector<int>> adj(N);
    vector<int> indeg(N);

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        indeg[v - 1]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> ans;
    while (!q.empty()) {
        int n = q.front(); q.pop();
        ans.push_back(n);
        
        for (auto x: adj[n]) {
            if (--indeg[x] == 0) {
                q.push(x);
            }
        }
    }

    if (ans.size() == N) {
        for (auto x: ans) cout << x + 1 << ' '; cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
}