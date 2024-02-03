#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<tuple<int, int, int>>> adj(n);
    vector<array<int, 3>> edges(m);

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a - 1].emplace_back(b - 1, i, c);
        adj[b - 1].emplace_back(a - 1, i, c);

        edges[i] = {a - 1, b - 1, c};
    }

    vector<bool> taken(m);
    vector<int> best, cc;

    do {
        cc.assign(n, -1);
        best.assign(n, -1);

        for (int i = 0; i < n; i++) {
            if (cc[i] != -1) continue;
            
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int node = q.front(); q.pop();
                if (cc[node] != -1) continue;
                cc[node] = i;

                for (auto [x, idx, w]: adj[node]) {
                    if (taken[idx]) q.push(x);
                }
            }
        }

        for (int i = 0; i < m; i++) {
            auto [a, b, c] = edges[i];
            if (cc[a] == cc[b]) continue;

            if (best[cc[a]] == -1 || c < edges[best[cc[a]]][2]) {
                best[cc[a]] = i;
            }
            if (best[cc[b]] == -1 || c < edges[best[cc[b]]][2]) {
                best[cc[b]] = i;
            }
        }

        for (auto x: best) {
            if (x != -1) {
                taken[x] = true;
            }
        }
    } while (any_of(best.begin(), best.end(), [](int x) { return x != -1; }));

    if (any_of(cc.begin(), cc.end(), [](int x) { return x != 0; })) {
        cout << "IMPOSSIBLE\n";
    } else {
        long long cost = 0;
        for (int i = 0; i < m; i++) {
            cost += taken[i] * edges[i][2];
        }

        cout << cost << '\n';
    }
}