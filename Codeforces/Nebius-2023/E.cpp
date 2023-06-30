#include <bits/stdc++.h>
using namespace std;

#define MAXN 20

int n, m;
vector<int> adj[MAXN];

bitset<MAXN> visited;
vector<int> path;

int start;

bool control() {
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        if (!any_of(adj[i].begin(), adj[i].end(), [&](int a) { return visited[a]; })) return false;
    }
    return true;
}

void print() {
    vector<int> next(n);
    for (int i = 0; i < path.size() - 1; i++) {
        next[path[i]] = path[i + 1] + 1;
    }
    next[path[path.size() - 1]] = path[0] + 1;
    
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        for (auto x: adj[i]) {
            if (visited[x]) {
                next[i] = x + 1;
                break;
            }
        }
    }

    cout << "Yes\n";
    for (auto x: next) cout << x << " ";
    exit(0);
}

void dfs(int node) {
    if ((clock() - start) > CLOCKS_PER_SEC / 20) return;
    visited.set(node);
    path.push_back(node);

    for (auto x: adj[node]) {
        if (x == path[0]) {
            if (control()) {
                print();
            }
        } else if (!visited[x]) {
            dfs(x);
        }
    }
    path.pop_back();
    visited.reset(node);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < n; i++) {
        start = clock();
        dfs(i);
    }
    cout << "No\n";
}