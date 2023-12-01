#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    int s = 1 << (int)ceil(log2(n));

    vector<int> scc(4 * s);
    vector<int> q;
    vector<vector<int>> common_edges(4 * s);
    vector<vector<int>> special_edges(4 * s);
    vector<vector<int>> rev_edges(4 * s);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        common_edges[2 * (u + s) | 1].push_back(2 * (v + s));
        common_edges[2 * (v + s) | 1].push_back(2 * (u + s));
    }

    for (int i = 1; i < s; i++) {
        common_edges[2 * i | 1].push_back(2 * (2 * i) | 1);
        common_edges[2 * i | 1].push_back(2 * (2 * i + 1) | 1);
        common_edges[2 * (2 * i)].push_back(2 * i);
        common_edges[2 * (2 * i + 1)].push_back(2 * i);
    }

    function<void(int)> dfs_1 = [&](int node) {
        scc[node] = -1;
        for (auto n: common_edges[node]) {
            if (scc[n] == -1) continue;
            dfs_1(n);
        }
        for (auto n: special_edges[node]) {
            if (scc[n] == -1) continue;
            dfs_1(n);
        }
        q.push_back(node);
    };

    function<void(int, int)> dfs_2 = [&](int node, int root) {
        scc[node] = root;
        for (auto n: rev_edges[node]) {
            if (scc[n] != -1) continue;
            dfs_2(n, root);
        }
    };
 
    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        for (auto &arr: special_edges) arr.clear();
        for (auto &arr: rev_edges) arr.clear();

        for (int i = 0; i < n; i++) {
            for (int ll = i + 1 + s, rr = min(n, i + m) + s; ll < rr; ll >>= 1, rr >>= 1) {
                if (ll & 1) {
                    special_edges[2 * (i + s)].push_back(2 * ll | 1);
                    special_edges[2 * ll].push_back(2 * (i + s) | 1);
                    ll++;
                }
                if (rr & 1) {
                    rr--;
                    special_edges[2 * (i + s)].push_back(2 * rr | 1);
                    special_edges[2 * rr].push_back(2 * (i + s) | 1);
                }
            }
            for (int ll = max(0, i - m + 1) + s, rr = i + s; ll < rr; ll >>= 1, rr >>= 1) {
                if (ll & 1) {
                    special_edges[2 * (i + s)].push_back(2 * ll | 1);
                    special_edges[2 * ll].push_back(2 * (i + s) | 1);
                    ll++;
                }
                if (rr & 1) {
                    rr--;
                    special_edges[2 * (i + s)].push_back(2 * rr | 1);
                    special_edges[2 * rr].push_back(2 * (i + s) | 1);
                }
            }
        }

        for (int i = 0; i < 4 * s; i++) {
            for (auto x: common_edges[i]) {
                rev_edges[x].push_back(i);
            }
            for (auto x: special_edges[i]) {
                rev_edges[x].push_back(i);
            }
        }

        fill(scc.begin(), scc.end(), 0);
        q.clear();
        for (int i = 0; i < 4 * s; i++) {
            if (scc[i] != -1) dfs_1(i);
        }

        for (int i = 4 * s - 1; i >= 0; i--) {
            if (scc[q[i]] == -1) dfs_2(q[i], q[i]);
        }

        bool ok = true;
        for (int i = 0; i < 2 * s; i++) {
            if (scc[2 * i] == scc[2 * i | 1]) {
                ok = false;
                break;
            }
        }

        if (ok) l = m;
        else r = m;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}