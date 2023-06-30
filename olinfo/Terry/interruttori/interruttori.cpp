#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N, A, B;
    cin >> N >> A >> B;

    vector<int> adj[N];
    queue<pair<int, int>> q;

    for (int i = 0; i < A; i++) {
        int Z; cin >> Z;
        q.push({Z, 1});
    }

    for (int i = 0; i < B; i++) {
        int X, Y; cin >> X >> Y;
        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }

    int d, i;
    vector<bool> visited(N, false);

    while (!q.empty()) {
        auto [node, dst] = q.front();
        q.pop();
        if (visited[node]) continue;

        i = node, d = dst;
        visited[node] = true;

        for (auto x: adj[node])
            if (!visited[x])
                q.push({x, dst + 1});
    }
    cout << "Case #" << t << ": " << i << " " << d << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
