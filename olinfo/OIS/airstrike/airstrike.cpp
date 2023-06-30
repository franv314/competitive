#include <bits/stdc++.h>
using namespace std;

#define MAXN 10'000
#define SOURCE 0
#define SINK 20'001

unordered_set<int> adj[2 * MAXN + 2];
bitset<2 * MAXN + 2> visited;
vector<int> path;

vector<int> adj2[2 * MAXN + 2];

bool dfs(int node) {
    visited.set(node);
    path.push_back(node);
    if (node == SINK) return true;

    for (auto n: adj[node]) {
        if (visited[n]) continue;
        if (dfs(n)) return true;
    }
    path.pop_back();
    return false;
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int X, Y; cin >> X >> Y;
        
        adj[SOURCE].insert(X);
        adj[X].insert(Y + MAXN);
        adj[Y + MAXN].insert(SINK);
    }

    for (;;) {
        visited.reset();
        path.clear();
        if (!dfs(SOURCE)) break;

        for (int i = 0; i < path.size() - 1; i++) {
            adj[path[i]].erase(path[i + 1]);
            adj[path[i + 1]].insert(path[i]);
        }
    }

    set<int> q;
    for (int i = 1; i <= N; i++) {
        q.insert(i);
    }
    for (int i = MAXN + 1; i <= 2 * MAXN; i++) {
        for (auto x: adj[i]) {
            q.erase(x);
        }
    }

    visited.reset();
    while (!q.empty()) {
        auto curr = *q.begin(); q.erase(q.begin());
        if (visited[curr]) continue;
        visited[curr] = true;
        for (auto n: adj2[curr]) {
            if (!visited[n]) {
                q.insert(n);
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) count++;
        if (visited[i + MAXN]) count++;
    }
    cout << count << "\n";
}