#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n, m; cin >> n >> m;
    int p, b; cin >> p >> b;

    vector<bool> bonus(n), token(n);
    vector<int> tokens;
    for (int i = 0; i < p; i++) {
        int x; cin >> x;
        tokens.push_back(x - 1);
        token[x - 1] = true;
    }
    bonus[0] = true;
    for (int i = 0; i < b; i++) {
        int x; cin >> x;
        bonus[x - 1] = true;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int needed_moves;
    int skip;

    queue<pair<int, int>> q;
    vector<bool> visited(n);
    q.push({0, 0});
    while (!q.empty()) {
        auto [pos, dst] = q.front(); q.pop();
        if (visited[pos]) continue;

        if (token[pos]) {
            skip = pos;
            needed_moves = dst;
            break;
        }

        visited[pos] = true;
        for (auto x: adj[pos]) {
            if (bonus[pos] && !visited[x]) {
                q.push({x, dst + 1});
            }
        }
    }

    int tempos = 0;
    for (auto t: tokens) {
        if (t == skip) continue;
        bool ok = false;
        for (auto x: adj[t]) {
            if (bonus[x]) {
                ok = true;
                for (auto y: adj[x]) {
                    if (bonus[y]) {
                        return true;
                    }
                }
            }
        }
        tempos += ok;
    }
    return (tempos + 1) >= needed_moves;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    
    while (t--) {
        cout << (solve() ? "YES\n" : "NO\n");
    }
}