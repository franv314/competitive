#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, P; cin >> N >> M >> P;
    vector<vector<int>> adj(N);
    vector<int> in(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        in[v]++;
    }

    queue<int> q;
    q.emplace(0);
    vector<double> p(N);
    p[0] = 1.0;

    while (!q.empty()) {
        int n = q.front(); q.pop();
        
        for (auto x: adj[n]) {
            p[x] += p[n] / adj[n].size();
            if (--in[x] == 0) {
                q.push(x);
            }
        }
    }

    cout << max_element(p.begin() + N - P, p.end()) - p.begin() << '\n';
}