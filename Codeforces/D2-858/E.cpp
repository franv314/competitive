#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

constexpr int BLOCK = 512;

int n, q, a[MAXN], p[MAXN];
vector<int> children[MAXN];

long long val[MAXN];
vector<int> bin_lift[MAXN];

int depth[MAXN];
int pos_in_dfs[MAXN];
vector<int> dfs_order;

void update(long long &val, long long old, long long n, int cnt_o, int cnt_n) {
    if (cnt_o != 2) old = 0;
    if (cnt_n != 2) n = 0;
    val += (n - old);
}

void dfs(int node, vector<int> &path) {
    depth[node] = path.size();
    pos_in_dfs[node] = dfs_order.size();
    dfs_order.push_back(node);
    
    val[node] = val[p[node]] + a[node] * (long long)a[node];

    for (int o = 1; o <= path.size(); o <<= 1) {
        bin_lift[node].push_back(path[path.size() - o]);
    }

    for (auto child: children[node]) {
        path.push_back(node);
        dfs(child, path);
        path.pop_back();
    }
    
    dfs_order.push_back(node);
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        children[p[i]].push_back(i);
    }

    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }

    vector<int> temp;
    dfs(1, temp);

    sort(queries.begin(), queries.end(), [&](array<int, 3> a, array<int, 3> b) {
        int q1b = pos_in_dfs[a[0]], q1e = pos_in_dfs[a[1]];
        int q2b = pos_in_dfs[b[0]], q2e = pos_in_dfs[b[1]];

        if (q1b > q1e) swap(q1b, q1e);
        if (q2b > q2e) swap(q2b, q2e);

        if (q1b / BLOCK != q2b / BLOCK) {
            return q1b < q2b;
        } else if ((q1b / BLOCK) & 1) {
            return q1e > q2e;
        } else {
            return q1e < q2e;
        }
    });

    vector<bool> inside(n + 1, false);
    long long vval = 0;
    vector<long long> depths(n, 1);
    vector<int> cnt(n, 0);
    vector<long long> ans(q);
    int l = 0, r = 0;
    for (auto [x, y, i]: queries) {
        int b = pos_in_dfs[x], e = pos_in_dfs[y];
        if (b > e) swap(b, e);
        b++, e++;

        while (r < e) {
            int node = dfs_order[r];

            long long new_depth = depths[depth[node]];
            int old_cnt = cnt[depth[node]];
            if (inside[node]) {
                new_depth /= a[node];
                cnt[depth[node]]--;
            } else {
                new_depth *= a[node];
                cnt[depth[node]]++;
            }
            inside[node] = !inside[node];
            update(vval, depths[depth[node]], new_depth, old_cnt, cnt[depth[node]]);
            depths[depth[node]] = new_depth;

            r++;
        }
        while (r > e) {
            r--;
            int node = dfs_order[r];

            long long new_depth = depths[depth[node]];
            int old_cnt = cnt[depth[node]];
            if (inside[node]) {
                new_depth /= a[node];
                cnt[depth[node]]--;
            } else {
                new_depth *= a[node];
                cnt[depth[node]]++;
            }
            inside[node] = !inside[node];
            update(vval, depths[depth[node]], new_depth, old_cnt, cnt[depth[node]]);
            depths[depth[node]] = new_depth;
        }
        while (l < b) {
            int node = dfs_order[l];

            long long new_depth = depths[depth[node]];
            int old_cnt = cnt[depth[node]];
            if (inside[node]) {
                new_depth /= a[node];
                cnt[depth[node]]--;
            } else {
                new_depth *= a[node];
                cnt[depth[node]]++;
            }
            inside[node] = !inside[node];
            update(vval, depths[depth[node]], new_depth, old_cnt, cnt[depth[node]]);
            depths[depth[node]] = new_depth;

            l++;
        }
        while (l > b) {
            l--;
            int node = dfs_order[l];

            long long new_depth = depths[depth[node]];
            int old_cnt = cnt[depth[node]];
            if (inside[node]) {
                new_depth /= a[node];
                cnt[depth[node]]--;
            } else {
                new_depth *= a[node];
                cnt[depth[node]]++;
            }
            inside[node] = !inside[node];
            update(vval, depths[depth[node]], new_depth, old_cnt, cnt[depth[node]]);
            depths[depth[node]] = new_depth;
        }
        
        for (int k = bin_lift[x].size() - 1; k >= 0; k--) {
            if (bin_lift[x].size() > k && bin_lift[y].size() > k && bin_lift[x][k] != bin_lift[y][k]) {
                x = bin_lift[x][k], y = bin_lift[y][k];
            }
        }
        
        int lca = x == y ? x : p[x];
        
        ans[i] = vval + val[lca];
    }
    for (auto x: ans) cout << x << "\n";
}