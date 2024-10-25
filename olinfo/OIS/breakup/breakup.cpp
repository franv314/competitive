#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    int N, M; in >> N >> M;
    vector<vector<pair<int, int>>> dir_adj(N), inv_adj(N);

    for (int i = 0; i < M; i++) {
        int A, B, V; in >> A >> B >> V;
        dir_adj[A].emplace_back(B, V);
        inv_adj[B].emplace_back(A, V);
    }

    vector<int> bond(N);
    queue<int> changes;
    for (int i = 1; i < N - 1; i++) {
        for (auto [j, v]: dir_adj[i]) {
            if (j == N - 1) bond[i] -= v;
            else bond[i] += v;
        }

        if (bond[i] < 0)
            changes.push(i);
    }

    string ans = string(N - 1, 'W') + 'G';
    while (!changes.empty()) {
        int change = changes.front(); changes.pop();
        if (ans[change] == 'G') continue;
        ans[change] = 'G';

        for (auto [j, v]: inv_adj[change]) {
            bond[j] -= 2 * v;
            if (j != 0 && bond[j] < 0) {
                changes.push(j);
            }
        }
    }

    out << ans << '\n';
}