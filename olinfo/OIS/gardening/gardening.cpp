#include <bits/stdc++.h>
using namespace std;

#define LOG 17
typedef long long i64;

vector<int> P, C, S;
vector<vector<int>> adj;

vector<int> timer, depth;
vector<i64> cost_open, cost_close, children_sum;
vector<vector<pair<int, i64>>> lift;

int dfs1(int node, int t = 0, int d = 0) {
    depth[node] = d;
    cost_open[node] = (P[node] == -1 ? 0 : cost_open[P[node]]) + (!S[node] * C[node]);

    if (adj[node].empty()) {
        timer[node] = t;
        cost_close[node] = S[node] * C[node];
        return 1;
    }

    int leaf_count = 0;

    for (auto child: adj[node]) {
        int leaves = dfs1(child, t, d + 1);
        
        t += leaves;
        leaf_count += leaves;

        children_sum[node] += cost_close[child];
    }

    if (S[node]) {
        cost_close[node] = min((i64)C[node], children_sum[node]);
    }

    return leaf_count;
}

void dfs2(int node) {
    if (P[node] != -1) {
        lift[node].emplace_back(P[node], children_sum[P[node]] - cost_close[node]);
        for (;;) {
            auto [ancestor, cost] = lift[node].back();
            
            int idx = lift[node].size() - 1;
            if (lift[ancestor].size() <= idx) break;

            auto [ancestor2, cost2] = lift[ancestor][idx];
            lift[node].emplace_back(ancestor2, cost + cost2);
        }
    }

    for (auto child: adj[node]) {
        dfs2(child);
    }
}

pair<i64, int> merge(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int ou = u, ov = v;

    i64 cost = 0;
    
    for (int i = LOG; i >= 0; i--) {
        if (i < lift[v].size() && depth[lift[v][i].first] >= depth[u]) {
            cost += lift[v][i].second;
            v = lift[v][i].first;
        }
    }

    if (u == v) {
        return {cost - children_sum[u] + cost_open[ov] - cost_open[u], u};
    }

    for (int i = LOG; i >= 0; i--) {
        if (i < lift[u].size() && lift[u][i].first != lift[v][i].first) {
            cost += lift[u][i].second + lift[v][i].second;
            u = lift[u][i].first;
            v = lift[v][i].first;
        }
    }

    int lca = P[u];
    return {
        cost - cost_close[u] - cost_close[v] + cost_open[ou] + cost_open[ov] - 2 * cost_open[lca],
        lca
    };
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, Q; cin >> N >> Q;

    P.resize(N);
    C.resize(N);
    S.resize(N);
    adj.resize(N);

    for (auto &p: P) cin >> p;
    for (auto &c: C) cin >> c;
    for (auto &s: S) cin >> s;

    int root;
    for (int i = 0; i < N; i++) {
        if (P[i] == -1) root = i;
        else adj[P[i]].push_back(i);
    }

    timer.resize(N, -1);
    depth.resize(N);
    cost_open.resize(N);
    cost_close.resize(N);
    children_sum.resize(N);
    dfs1(root);

    lift.resize(N);
    dfs2(root);

    while (Q--) {
        int M; cin >> M;
        
        if (M == 0) {
            cout << cost_close[root] << '\n';
            continue;
        }
        
        vector<int> A(M);
        for (auto &a: A) cin >> a;

        sort(A.begin(), A.end(), [&](int u, int v){ return timer[u] < timer[v]; });

        i64 total = 0;

        set<int> lcas;
        stack<int> st;
        st.push(A[0]);

        for (int i = 1; i < A.size(); i++) {
            int nxt = A[i];

            while (!st.empty()) {
                auto [cost, lca1] = merge(st.top(), nxt);
                if (i + 1 != A.size()) {
                    auto [_, lca2] = merge(nxt, A[i + 1]);
                    if (depth[lca1] < depth[lca2]) {
                        break;
                    }
                }

                total += cost;
                lcas.insert(lca1);
                nxt = lca1;
                st.pop();
            }

            st.push(nxt);
        }

        if (st.top() != root) {
            lcas.insert(root);
            total += merge(st.top(), root).first;
        }

        for (auto lca: lcas) {
            total += children_sum[lca];
        }

        cout << total + cost_open[root] << '\n';
    }
}