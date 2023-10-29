#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int n, k1, k2; cin >> n >> k1 >> k2;
    vector<vector<int>> adj(n);
 
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    vector<int> sizes(n);
    vector<bool> gone(n);
    vector<int> freqs(n), temp_freqs(n);
    vector<long long> ps(n + 1);
    long long ans = 0;
 
    auto get_sizes = [&](auto &&get_sizes, int node, int par) -> int {
        sizes[node] = 1;
        for (auto c: adj[node]) {
            if (c == par || gone[c]) continue;
            sizes[node] += get_sizes(get_sizes, c, node);
        }
        return sizes[node];
    };
 
    auto dfs = [&](auto &&dfs, int node, int par, int d) -> void {
        temp_freqs[d]++;
 
        for (auto c: adj[node]) {
            if (c == par || gone[c]) continue;
            dfs(dfs, c, node, d + 1);
        }
    };
 
    auto decompose = [&](auto&&decompose, int root) -> void {
        int tot_size = get_sizes(get_sizes, root, -1);
 
        int centroid = root;
        bool ok;
        do {
            ok = true;
            for (auto x: adj[centroid]) {
                if (!gone[x] && sizes[x] < sizes[centroid] && sizes[x] * 2 > tot_size) {
                    centroid = x;
                    ok = false;
                    break;
                }
            }
        } while (!ok);
 
        freqs[0] = 1;
        for (auto x: adj[centroid]) {
            if (!gone[x]) {
                dfs(dfs, x, centroid, 1);

                int r;
                ps[1] = 0;
                for (int i = 1; i < n; i++) {
                    if (temp_freqs[i] == 0) {
                        r = i;
                        break;
                    }
                    freqs[i] += temp_freqs[i];
                    ps[i + 1] = ps[i] + temp_freqs[i];
                }

                for (int i = 1; i < n; i++) {
                    if (temp_freqs[i] == 0) break;
                    ans -= temp_freqs[i] * (ps[min(r, max(k2 + 1 - i, 0))] - ps[min(r, max(k1 - i, 0))]);
                    temp_freqs[i] = 0;
                }
            }
        }
 
        int r;
        for (int i = 0; i < n; i++) {
            if (freqs[i] == 0) {
                r = i;
                break;
            }
            ps[i + 1] = ps[i] + freqs[i];
        }

        for (int i = 0; i < n; i++) {
            if (freqs[i] == 0) break;
            ans += freqs[i] * (ps[min(r, max(k2 + 1 - i, 0))] - ps[min(r, max(k1 - i, 0))]);
            freqs[i] = 0;
        }

        gone[centroid] = true;
        for (auto x: adj[centroid]) {
            if (!gone[x]) {
                decompose(decompose, x);
            }
        }
    };
 
    decompose(decompose, 0);
    cout << ans / 2 << '\n';
}