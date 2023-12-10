#include <bits/stdc++.h>
using namespace std;

int GetMove();
void MakeMove(int v);

void SocialEngineering(int n, int m, vector<pair<int, int>> edges) {
    vector<vector<int>> adj(n);
    vector<bool> is_link(n);

    for (auto [u, v]: edges) {
        if (u > v) swap(u, v);
        u--, v--;
        if (u == 0) {
            is_link[v] = true;
        } else {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> next(n);
    vector<bool> visited(n);
    vector<shared_ptr<vector<int>>> paths(n);

    function<shared_ptr<vector<int>>(int)> dfs = [&](int node) -> shared_ptr<vector<int>> {
        visited[node] = true;
        
        shared_ptr<vector<int>> x = NULL;
        if (is_link[node]) {
            x = make_shared<vector<int>>();
        }

        for (auto n: adj[node]) {
            if (visited[n]) continue;

            shared_ptr<vector<int>> path = dfs(n);
            if (!path) continue;

            if (!x) {
                x = path;
                continue;
            }

            x->push_back(node);
            copy(path->rbegin(), path->rend(), back_inserter(*x));
            paths[x->front()] = paths[x->back()] = x;
            x = NULL;
        }

        if (x) x->push_back(node);
        return x;
    };

    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            shared_ptr<vector<int>> path = dfs(i);
            if (path) {
                return;
            }
        }
    }

    while (int move = GetMove()) {
        move--;
        vector<int> path = *paths[move];
        if (path[0] != move) reverse(path.begin(), path.end());

        for (int i = 1; i < path.size(); i++) {
            MakeMove(path[i] + 1);
        }
        MakeMove(1);
    }
}