#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 200000
#define $ << " " <<
 
int n;
vector<int> adj[MAXN];
 
bitset<MAXN> visited;
int subtree_size[MAXN];
long long root_dst;
 
long long ans[MAXN];
 
int dfs(int node, int depth) {
    root_dst += depth;
    visited.set(node);
    subtree_size[node] = 1;
 
    for (auto child: adj[node]) {
        if (!visited[child]) {
            subtree_size[node] += dfs(child, depth + 1);
        }
    }
    return subtree_size[node];
}
 
void dfs_ans(int node) {
    ans[node] = root_dst;
    visited.set(node);
 
    for (auto child: adj[node]) {
        if (!visited[child]) {
            root_dst += n - 2 * subtree_size[child];
            dfs_ans(child);
            root_dst -= n - 2 * subtree_size[child];
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
 
    cin >> n;
    for (int _ = 1; _ < n; _++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
 
    assert(dfs(0, 0) == n);
 
    visited.reset();
    dfs_ans(0);
 
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
}