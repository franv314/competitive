#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> ans;
vector<int> st;
int N, K;

void dfs(int node, int par) {
    st.push_back(node);
    if (st.size() > K) ans[node] = st[st.size() - 1 - K];

    for (auto &x: adj[node]) {
        if (x == par) continue;
        dfs(x, node);
    }
    st.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    
    adj.resize(N);
    ans.assign(N, -1);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(0, -1);

    for (auto x: ans) cout << x << ' '; cout << '\n';
}