#include <bits/stdc++.h>
using namespace std;

#define MAXN 10'000
#define MAXC 100

int N, C, T[MAXN];
vector<int> adj[MAXN];

long long temp[MAXC + 1];
long long dp[MAXN][MAXC + 1];

void dfs(int node) {
    if (adj[node].empty()) {
        dp[node][0] = T[node];
        fill(&dp[node][1], &dp[node][101], 0);
        return;
    }

    priority_queue<tuple<long long, int, int>> children;
    for (auto child: adj[node]) {
        dfs(child);
        children.push({dp[child][0], 0, child});
    }

    temp[0] = get<0>(children.top());
    for (int cheats = 1; cheats <= C; cheats++) {
        auto [cost, cheats_used, child] = children.top(); children.pop();
        cost = dp[child][++cheats_used];
        children.push({cost, cheats_used, child});

        temp[cheats] = get<0>(children.top()); 
    }

    dp[node][0] = temp[0] + T[node];
    for (int cheats = 1; cheats <= C; cheats++) {
        dp[node][cheats] = min(temp[cheats] + T[node], temp[cheats - 1]);
    }
}

int main() {
    cin >> N >> C;
    int root;
    for (int i = 0; i < N; i++) {
        int P; cin >> P >> T[i];

        if (P != -1) adj[P].push_back(i);
        else root = i;
    }

    dfs(root);

    cout << dp[root][C];
}