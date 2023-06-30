#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 1'000'000
#define MAXLOG 20

int *T;

vector<pair<int, long long>> children[MAXN + 1];
int ancestors[MAXN + 1][MAXLOG];
vector<long long> dfs_prefixes(1);
int pos_in_dfs[MAXN + 1];

void dfs(vector<int> &path, long long distance) {
    int node = path.back();
    int depth = path.size() - 1;

    pos_in_dfs[node] = dfs_prefixes.size();
    dfs_prefixes.push_back(dfs_prefixes.back() + distance);

    for (auto [child, weight]: children[node]) {
        path.push_back(child);

        dfs(path, weight);

        path.pop_back();
    }

    dfs_prefixes.push_back(dfs_prefixes.back() - distance);

    for (int i = 0; (1 << i) <= depth; i++) {
        ancestors[node][i] = path[depth - (1 << i)];
    }
}

void inizia(int N, int T[]) {
    ::T = T;

    stack<pair<int, int>> min_stack;
    for (int i = N - 1; i >= 0; i--) {
        while (!min_stack.empty() && min_stack.top().second >= T[i])
            min_stack.pop();
        
        if (min_stack.empty())
            children[N].push_back({i, (N - i) * T[i]});
        else
            children[min_stack.top().first].push_back({i, (min_stack.top().first - i) * (long long)T[i]});
        
        min_stack.push({i, T[i]});
    }
    
    vector<int> path(1, N);

    dfs(path, 0);
}

long long passaggio(int L, int R) {
    int l = L;
    
    for (int i = 19; i >= 0; i--) {
        if (ancestors[l][i] && ancestors[l][i] <= R) {
            l = ancestors[l][i];
        }
    }

    return (R - l) * (long long)T[l] - (dfs_prefixes[pos_in_dfs[l]] - dfs_prefixes[pos_in_dfs[L]]);
}