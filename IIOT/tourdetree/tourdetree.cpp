#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

vector<pair<int, int>> adj[MAXN];
long long dst[MAXN];

void dfs(int node, long long d = 0, int par = -1) {
    dst[node] = d;
    for (auto [c, w]: adj[node]) {
        if (c == par) continue;
        dfs(c, d + w, node);
    }
}

int main() {
    int N, K; cin >> N >> K;
    long long tot = 0;
    
    for (int i = 0; i < N - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        tot += c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    if (K == 1) {
        cout << 2 * tot;
        return 0;
    }

    dfs(1);
    int farthest = max_element(dst + 1, dst + N + 1) - dst;
    dfs(farthest);
    long long diameter = *max_element(dst + 1, dst + N + 1);
    cout << 2 * tot - diameter;
}