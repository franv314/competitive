#include <bits/stdc++.h>
using namespace std;

#define BITS 19

int solve(int N, int M, const vector<int> &C, const vector<int> &A, const vector<int> &B) {
    vector<vector<int>> by_color(N);
    for (int i = 0; i < N; i++)
        by_color[C[i]].push_back(i);

    vector<vector<int>> in_adj(N), out_adj(N);

    for (int i = 0; i < M; i++) {
        if (C[A[i]] == C[B[i]]) {
            in_adj[A[i]].push_back(B[i]);
            in_adj[B[i]].push_back(A[i]);
        } else {
            out_adj[A[i]].push_back(B[i]);
            out_adj[B[i]].push_back(A[i]);
        }
    }

    int ans = 1e9;
    vector<bool> visited(N);
    vector<int> dst(N, 1e9);

    for (int color = 0; color < N; color++) {
        vector<int> border[BITS][2];
        for (auto node: by_color[color]) {
            for (auto ext: out_adj[node]) {
                for (int b = 0; b < BITS; b++) {
                    if ((C[ext] >> b) & 1)
                        border[b][1].push_back(node);
                    else
                        border[b][0].push_back(node);
                }
            }
        }

        for (int b = 0; b < BITS; b++) {
            queue<pair<int, int>> q;
            for (auto node: border[b][0])
                q.emplace(node, 0);
            
            while (!q.empty()) {
                auto [node, d] = q.front(); q.pop();
                if (visited[node]) continue;
                
                visited[node] = true;
                dst[node] = d;

                for (auto x: in_adj[node])
                    q.emplace(x, d + 1);
            }

            for (auto node: border[b][1]) {
                ans = min(ans, dst[node]);
            }

            for (auto node: by_color[color]) {
                dst[node] = 1e9;
                visited[node] = false;
            }
        }
    }

    if (ans == 1e9) ans = -1;
    else ans += 2;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    
    vector<int> C(N);
    for (auto &x: C) cin >> x;

    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++)
        cin >> A[i] >> B[i];

    cout << solve(N, M, C, A, B) << '\n';
}