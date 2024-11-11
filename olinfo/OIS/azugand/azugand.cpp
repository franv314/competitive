#include <bits/stdc++.h>
using namespace std;

#define MAXBITS 20

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int N, Q; cin >> N >> Q;
    
    vector<int> A(N);
    for (auto &x: A)
        cin >> x;

    vector<vector<int>> adj(N + MAXBITS);
    for (int i = 0; i < N; i++) {
        for (int b = 0; b < MAXBITS; b++) {
            if ((A[i] >> b) & 1) {
                adj[i].push_back(N + b);
                adj[N + b].push_back(i);
            }       
        }
    }

    vector<vector<int>> dst(MAXBITS, vector<int>(N + MAXBITS, 1e9));
    for (int b = 0; b < MAXBITS; b++) {
        queue<int> q;

        q.push(N + b);
        dst[b][N + b] = 0;

        while (!q.empty()) {
            int x = q.front(); q.pop();

            for (auto y: adj[x]) {
                if (dst[b][y] == 1e9) {
                    dst[b][y] = dst[b][x] + 1;
                    q.push(y);
                }
            }
        }
    }

    while (Q--) {
        int u, v; cin >> u >> v;
        u--, v--;

        int ans = 1e9;
        for (int b = 0; b < MAXBITS; b++)
            if ((A[u] >> b) & 1)
                ans = min(ans, 1 + dst[b][v]);

        if (ans == 1e9)
            cout << "-1\n";
        else
            cout << ans / 2 << '\n';
    }
}