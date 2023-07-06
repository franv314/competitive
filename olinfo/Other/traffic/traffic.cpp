#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main() {
    int N; in >> N;
    vector<int> f(N);
    vector<vector<int>> adj(N);
    for (auto &x: f) in >> x;
    for (int i = 1; i < N; i++) {
        int u, v; in >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    long long total = accumulate(f.begin(), f.end(), 0ll);
    
    long long ans = LLONG_MAX;
    function<long long(int, int)> dfs = [&](int node, int parent) -> long long {
        long long sum = 0;
        long long ma = LLONG_MIN;
        for (auto n: adj[node]) {
            if (n == parent) continue;
            long long c_size = dfs(n, node);
            sum += c_size;
            ma = max(ma, c_size);
        }
        sum += f[node];
        ma = max(ma, total - sum);
        ans = min(ans, ma);
        return sum;
    };
    
    dfs(0, -1);
    
    out << ans;
}