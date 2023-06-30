#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001

void dfs(long long node, vector<vector<long long>> &adj, vector<long long> &no) {
    if (node == 0) return;
    
    no[node] = 1;
    for (auto x: adj[node]) {
        dfs(x, adj, no);
        no[node] += no[x];
    }
}

long long solve_tc() {
    long long n; cin >> n;
    vector<long long> a(n + 1);
    vector<vector<long long>> adj(n + 1);
    vector<long long> start;
    vector<bool> visited(n + 1);
    for (long long i = 1; i <= n; i++) {
        cin >> a[i];
        long long goes_to = i + a[i];
        if (1 <= goes_to && goes_to <= n) {
            adj[goes_to].push_back(i);
        } else {
            start.push_back(i);
        }
    }


    long long looped = n;
    
    long long my_path = 0;
    vector<long long> mpath;
    for (long long curr = 1; 1 <= curr && curr <= n; curr += a[curr]) {
        if (visited[curr]) {
            my_path *= -1;
            break;
        }
        visited[curr] = true;
        my_path++;
        mpath.push_back(curr);
    }

    vector<long long> no_of_loopables(n + 1);
    for (auto x: start) {
        dfs(x, adj, no_of_loopables);
        looped -= no_of_loopables[x];
    }


    if (my_path > 0) {
        long long ans = (n - my_path) * (2 * n + 1);
        for (auto i: mpath) {
            ans += 2 * n + 1 - no_of_loopables[i] - looped;
        }
        return ans;
    } else {
        my_path *= -1;
        return my_path * (2 * n + 1 - looped);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    long long t; cin >> t;
    while (t--) {
        cout << solve_tc() << "\n";
    }
}