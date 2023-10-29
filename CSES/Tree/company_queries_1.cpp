#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> p(n, -1);
    vector<vector<int>> adj(n);
    vector<vector<int>> bin_lift(n);

    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        adj[p[i]].push_back(i);
    }

    function<void(int)> dfs = [&](int node) {
        int curr = p[node];
        for (int h = 0; curr != -1; h++) {
            bin_lift[node].push_back(curr);
            curr = bin_lift[curr].size() > h ? bin_lift[curr][h] : -1;
        }

        for (auto c: adj[node]) {
            dfs(c);
        }
    };

    auto query = [&](int node, int k) {
        for (int i = 0; k != 0; k >>= 1, i++) {
            if (k & 1) {
                if (bin_lift[node].size() <= i) return -2;
                node = bin_lift[node][i];
            }
        }
        return node;
    };

    dfs(0);
    while (q--) {
        int n, k; cin >> n >> k;
        cout << 1 + query(n - 1, k) << '\n';
    }
}