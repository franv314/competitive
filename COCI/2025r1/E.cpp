#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    
    vector<array<int, 2>> edges(n - 3);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        tie(u, v) = minmax(u - 1, v - 1);
    }

    sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
        return a[1] - a[0] < b[1] - b[0];
    });

    vector<pair<int, int>> nxt(n);
    for (int i = 0; i < n; i++) {
        nxt[i] = {(i + 1) % n, -1};
    }

    vector<vector<int>> children;

    for (auto [l, r]: edges) {
        int curr = children.size();
        children.emplace_back();

        int i = l;
        while (i != r) {
            if (nxt[i].second != -1) {
                children[curr].push_back(nxt[i].second);
            }

            int p = i;
            i = nxt[i].first;
            nxt[p] = {-1, -1};
        }
        nxt[l] = {r, curr};
    }

    children.emplace_back();
    for (int i = 0; i < n; i++) {
        if (nxt[i].second != -1) {
            children.back().push_back(nxt[i].second);
        }
    }

    long long ans = 0;

    auto dfs = [&](auto &&dfs, int node) -> long long {
        long long cnt = 1;
        for (auto x: children[node]) {
            (cnt *= (dfs(dfs, x) + 1)) %= MOD;
        }

        (ans += cnt) %= MOD;
        return cnt;
    };

    dfs(dfs, children.size() - 1);
    
    cout << ans << '\n';
}