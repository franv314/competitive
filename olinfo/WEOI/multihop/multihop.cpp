#include <bits/stdc++.h>
using namespace std;

vector<int> A, B;
int C;
vector<vector<int>> adj;

struct Info {
    long long cost[2][2];
    int last;

    Info() { last = -1; }
    Info(int node) {
        last = node;
        cost[0][0] = A[node];
        cost[0][1] = B[node] + C;
        cost[1][0] = 1e13;
        cost[1][1] = C;
    }
};

Info merge(const Info &a, const Info &b) {
    if (a.last == -1) return b;
    if (b.last == -1) return a;

    Info ans;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            ans.cost[x][y] = min(
                min(a.cost[x][0], a.cost[x][1]) + b.cost[0][y],
                a.cost[x][1] + b.cost[1][y]
            );
        }
    }
    ans.last = b.last;
    return ans;
}

vector<int> depth;
vector<vector<pair<int, Info>>> up_lift, down_lift;

void init(int N, int C, vector<int> A, vector<int> B, vector<int> U, vector<int> V) {
    ::A = A, ::B = B, ::C = C;
    adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }

    depth.resize(N);
    up_lift.resize(N);
    down_lift.resize(N);

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> void {
        depth[node] = d;

        if (par != -1) {
            up_lift[node].emplace_back(par, Info(node));
            down_lift[node].emplace_back(par, Info(par));

            for (int i = 0; i < up_lift[up_lift[node][i].first].size(); i++) {
                int anc = up_lift[node][i].first;
                up_lift[node].emplace_back(
                    up_lift[anc][i].first,
                    merge(up_lift[node][i].second, up_lift[anc][i].second)
                );
                down_lift[node].emplace_back(
                    down_lift[anc][i].first,
                    merge(down_lift[anc][i].second, down_lift[node][i].second)
                );
            }
        }

        for (auto x: adj[node]) {
            if (x == par) continue;
            dfs(dfs, x, node, d + 1);
        }
    };

    dfs(dfs, 0);
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    for (int i = up_lift[v].size() - 1; i >= 0; i--) {
        if (i < up_lift[v].size() && depth[up_lift[v][i].first] >= depth[u]) {
            v = up_lift[v][i].first;
        }
    }

    if (u == v) return u;

    for (int i = up_lift[v].size() - 1; i >= 0; i--) {
        if (i < up_lift[v].size() && up_lift[v][i].first != up_lift[u][i].first) {
            u = up_lift[u][i].first;
            v = up_lift[v][i].first;
        }
    }

    return up_lift[u][0].first;
}

long long query(int X, int Y) {
    int L = lca(X, Y);

    Info up, down;

    for (int i = up_lift[X].size() - 1; i >= 0; i--) {
        if (i < up_lift[X].size() && depth[up_lift[X][i].first] >= depth[L]) {
            up = merge(up, up_lift[X][i].second);
            X = up_lift[X][i].first;
        }
    }
    for (int i = down_lift[Y].size() - 1; i >= 0; i--) {
        if (i < down_lift[Y].size() && depth[down_lift[Y][i].first] >= depth[L]) {
            down = merge(down_lift[Y][i].second, down);
            Y = down_lift[Y][i].first;
        }
    }

    Info ans = merge(up, down);
    return min(ans.cost[0][0], ans.cost[0][1]);
}
