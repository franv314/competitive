#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long closed, open;
    Info() : closed(0), open(0) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    long long total = 0;
    vector<vector<pair<int, int>>> treaties(N);
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        treaties[u - 1].emplace_back(v - 1, w);
        treaties[v - 1].emplace_back(u - 1, w);
        total += w;
    }

    vector<int> depth(N);
    vector<vector<int>> lift(N);

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> void {
        depth[node] = d;
        if (par != -1) {
            lift[node].push_back(par);
            for (int i = 0; i < lift[lift[node][i]].size(); i++)
                lift[node].push_back(lift[lift[node][i]][i]);
        }
        for (auto c: adj[node])
            if (c != par)
                dfs(dfs, c, node, d + 1);
    };

    auto lca = [&](int u, int v) {
        if (depth[u] > depth[v])
            swap(u, v);
        
        for (int i = lift[v].size() - 1; i >= 0; i--) {
            if (i < lift[v].size() && depth[lift[v][i]] >= depth[u]) {
                v = lift[v][i];
            }
        }

        if (u == v)
            return u;

        for (int i = lift[v].size() - 1; i >= 0; i--) {
            if (i < lift[v].size() && lift[v][i] != lift[u][i]) {
                v = lift[v][i];
                u = lift[u][i];
            }
        }

        return lift[u][0];
    };

    auto rise = [&](int u, int d) {
        for (int h = 0; d >> h; h++)
            if ((d >> h) & 1)
                u = lift[u][h];
        return u;
    };

    dfs(dfs, 0);
    vector<vector<tuple<int, int, int>>> by_lca(N);
    for (int i = 0; i < N; i++)
        for (auto [j, w]: treaties[i])
            if (i < j)
                by_lca[lca(i, j)].emplace_back(i, j, w);
    
    vector<long long> ans(N);

    auto calc = [&](auto &&calc, int node, int par = -1) -> Info {
        map<int, Info> children;
        for (auto c: adj[node])
            if (c != par)
                children[c] = calc(calc, c, node);
        
        long long closing = 0;
        for (auto [u, v, w]: by_lca[node]) {
            if (u == node || v == node) {
                if (u == node)
                    swap(u, v);
                int ru = rise(u, depth[u] - depth[node] - 1);
    
                children[ru].open -= w;
                children[ru].closed += w;
            } else {
                int ru = rise(u, depth[u] - depth[node] - 1);
                int rv = rise(v, depth[v] - depth[node] - 1);
    
                children[ru].open -= w;
                children[rv].open -= w;
                closing += w;
            }
        }

        long long closed_top = total - closing;
        for (auto [_, info]: children)
            closed_top -= info.open + info.closed;

        long long best = closed_top;
        for (auto [_, info]: children)
            best = max(best, closed_top + info.closed + info.open);

        long long ma1 = 0, ma2 = 0;
        for (auto [_, info]: children) {
            if (info.closed > ma1) {
                ma2 = ma1;
                ma1 = info.closed;
            } else if (info.closed > ma2) {
                ma2 = info.closed;
            }
        }

        best = max(best, ma1 + ma2);
        map<pair<int, int>, long long> special_children;

        for (auto [u, v, w]: by_lca[node]) {
            if (u != node && v != node) {
                int ru = rise(u, depth[u] - depth[node] - 1);
                int rv = rise(v, depth[v] - depth[node] - 1);
    
                int au = min(ru, rv);
                int av = max(ru, rv);

                if (!special_children.count({au, av}))
                    special_children[{au, av}] = children[au].closed + children[av].closed;

                special_children[{au, av}] += w;
                best = max(best, special_children[{au, av}]);
            }
        }

        ans[node] = best;

        Info out;
        for (auto [_, info]: children) {
            out.open += info.open;
            out.closed += info.closed;
        }
        out.closed += closing;

        for (auto [u, w]: treaties[node])
            if (lca(u, node) != node)
                out.open += w;

        return out;
    };

    calc(calc, 0);

    for (auto x: ans)
        cout << x << ' ';
    cout << '\n';
}
