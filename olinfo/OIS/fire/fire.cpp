#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define MAXN 200'000

struct {
    int sum;
    multiset<int, greater<int>> children_ans;

    void insert(int val) {
        sum += val;
        children_ans.insert(val);
    }

    void erase(int val) {
        sum -= val;
        children_ans.erase(children_ans.find(val));
    }

    int get_ans() { return 1 + sum - *children_ans.begin(); }
} calc[MAXN];

int answer[MAXN];
vector<int> adj[MAXN];

void dfs(int node, int par = -1) {
    for (auto child: adj[node]) {
        if (child != par) {
            dfs(child, node);
            calc[node].insert(calc[child].get_ans());
        }
    }
}

void update(int node, int par) {
    calc[par].erase(calc[node].get_ans());
    calc[node].insert(calc[par].get_ans());
}

void reroot(int node, int par = -1) {
    answer[node] = calc[node].get_ans();

    for (auto child: adj[node]) {
        if (child != par) {
            update(child, node);
            reroot(child, node);
            update(node, child);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N; cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0);
    reroot(0);
    for (int i = 0; i < N; i++) cout << answer[i] << " ";
}