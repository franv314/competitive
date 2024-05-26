#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> D(N);
    vector<vector<int>> C(N, vector<int>(N));

    for (auto &x: D) cin >> x;
    for (auto &row: C)
        for (auto &x: row) cin >> x;

    const int S = 2 * N, T = 2 * N + 1;
    vector<unordered_set<int>> adj(2 * N + 2);
    
    for (int i = 0; i < N; i++) {
        adj[S].insert(i);
        adj[i + N].insert(T);
        for (int j = 0; j < N; j++)
            if (i != j && D[i] + C[i][j] <= D[j])
                adj[i].insert(N + j);
    }

    int match = 0;
    for (;;) {
        vector<int> prec(2 * N + 2, -2);
        queue<int> q;
        q.push(S);
        prec[S] = -1;

        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (auto i: adj[x]) {
                if (prec[i] == -2) {
                    q.push(i);
                    prec[i] = x;
                } 
            }
        }

        if (prec[T] == -2) break;
        match++;

        vector<int> path;
        for (int curr = T; curr != -1; curr = prec[curr])
            path.push_back(curr);

        for (int i = 0; i < path.size() - 1; i++) {
            adj[path[i]].insert(path[i + 1]);
            adj[path[i + 1]].erase(path[i]);
        }
    }

    cout << N - match << '\n';
}