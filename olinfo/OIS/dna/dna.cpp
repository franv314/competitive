#include <bits/stdc++.h>
using namespace std;

#define G ((1 << 25) - 1)

int main() {
    int N, M; cin >> N >> M;
    vector<array<__uint128_t, 4>> S(N);
    cin.get();
    for (auto &x: S) {
        __uint128_t s = 0;
        char c;
        while ((c = cin.get()) != '\n') {
            s = s * 2 + c - 48;
        }

        x = {s & G, (s >> 25) & G, (s >> 50) & G, (s >> 75) & G};
    }

    vector<bool> visited(N);
    vector<int> came_from(N);
    vector<int> dst(N, 1e9);
    priority_queue<pair<int, int>> q;

    q.push({0, 0});

    int total_cost = M;
    came_from[0] = dst[0] = 0;
    while (!q.empty()) {
        auto [x, mi_idx] = q.top(); q.pop();
        if (visited[mi_idx]) continue;
        total_cost +=
            + __builtin_popcount(S[mi_idx][0] ^ S[came_from[mi_idx]][0])
            + __builtin_popcount(S[mi_idx][1] ^ S[came_from[mi_idx]][1])
            + __builtin_popcount(S[mi_idx][2] ^ S[came_from[mi_idx]][2])
            + __builtin_popcount(S[mi_idx][3] ^ S[came_from[mi_idx]][3]);
        visited[mi_idx] = true;
        for (int j = 0; j < N; j++) {
            if (j == mi_idx) continue;
            int new_dst =
                + __builtin_popcount(S[j][0] ^ S[mi_idx][0])
                + __builtin_popcount(S[j][1] ^ S[mi_idx][1])
                + __builtin_popcount(S[j][2] ^ S[mi_idx][2])
                + __builtin_popcount(S[j][3] ^ S[mi_idx][3]);
            if (new_dst < dst[j]) {
                dst[j] = new_dst;
                came_from[j] = mi_idx;
                q.push({-dst[j], j});
            }
        }
    }
    cout << total_cost << "\n";
}