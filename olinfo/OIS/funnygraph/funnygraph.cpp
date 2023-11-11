#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<vector<array<int, 3>>> adj(N);
    for (int i = 0; i < M; i++) {
        int a, b, z; cin >> a >> b >> z;
        adj[a].push_back({b, +z, i});
        adj[b].push_back({a, -z, i});
    }

    int l = -1, r = M;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        vector<long long> potential(N, LLONG_MAX);
        bool ok = true;

        for (int i = 0; i < N; i++) {
            if (potential[i] != LLONG_MAX) continue;
            potential[i] = 0;
            queue<int> q;
            q.push(i);

            while (!q.empty()) {
                int n = q.front(); q.pop();
                for (auto [x, z, t]: adj[n]) {
                    if (t > m) continue;
                    long long wp = z + potential[n];
                    if (potential[x] == LLONG_MAX || potential[x] == wp) {
                        if (potential[x] == LLONG_MAX) q.push(x);
                        potential[x] = wp;
                    } else {
                        ok = false;
                        goto out;
                    }
                }
            }
        }

        out:;
        if (ok) l = m;
        else r = m;
    }
    
    cout << l + 1 << '\n';
}