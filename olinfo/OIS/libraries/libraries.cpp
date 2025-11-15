#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> A(N), B(N), C(N);
    
    int P; cin >> P;
    for (int i = 0; i < P; i++) {
        int x; cin >> x;
        A[x] = true;
    }
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int x; cin >> x;
        B[x] = true;
    }
    int R; cin >> R;
    for (int i = 0; i < R; i++) {
        int x; cin >> x;
        C[x] = true;
    }

    vector<long long> ans(N);

    auto dfs = [&](auto &&dfs, int node, int par = -1) -> array<int, 3> {
        vector<array<int, 3>> children = {{A[node], B[node], C[node]}};
        array<int, 3> me = {A[node], B[node], C[node]};
        
        for (auto &x: adj[node]) {
            if (x == par) continue;
            array<int, 3> child = dfs(dfs, x, node);
            children.push_back(child);
            me[0] += child[0];
            me[1] += child[1];
            me[2] += child[2];
        }

        children.push_back({P - me[0], Q - me[1], R - me[2]});

        long long sum_a = 0, sum_b = 0, sum_c = 0, sum_ab = 0, sum_ac = 0, sum_bc = 0, sum_abc = 0;
        for (auto [a, b, c]: children) {
            sum_a += a;
            sum_b += b;
            sum_c += c;
            sum_ab += (long long)a * b;
            sum_ac += (long long)a * c;
            sum_bc += (long long)b * c;
            sum_abc += (long long)a * b * c;
        }

        ans[node] = sum_a * sum_b * sum_c
                  - sum_a * sum_bc - sum_b * sum_ac - sum_c * sum_ab
                  + 2 * sum_abc;

        if (A[node] && B[node]) ans[node] += R - C[node];
        if (A[node] && C[node]) ans[node] += Q - B[node];
        if (B[node] && C[node]) ans[node] += P - A[node];
        if (A[node] && B[node] && C[node]) ans[node]++;

        return me;
    };

    dfs(dfs, 0);

    for (auto x: ans) cout << x << ' '; cout << '\n';
}