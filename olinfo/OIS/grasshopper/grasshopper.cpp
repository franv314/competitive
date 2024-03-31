#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    vector<array<bool, 2>> visited(N);
    queue<pair<int, int>> q;
    q.emplace(0, 0);

    while (!q.empty()) {
        auto [node, status] = q.front(); q.pop();
        if (visited[node][status]) continue;
        visited[node][status] = true;

        for (auto x: adj[node]) {
            q.emplace(x, status ^ 1);
        }
    }

    cout << count_if(visited.begin(), visited.end(), [&](array<bool, 2> a) { return a[0]; }) << '\n';
}