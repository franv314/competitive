#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> eliminations(n + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        eliminations[x].push_back(i);
    }

    long long m; cin >> m;
    vector<int> cols(n, INT_MIN);

    map<int, long long> freqs;
    unordered_map<int, long long> curr_freqs;
    curr_freqs.max_load_factor(0.25);
    curr_freqs.reserve(2048);

    function<int(int)> find = [&](int node) {
        if (cols[node] < 0) return node;
        return cols[node] = find(cols[node]);
    };

    function<void(int, int)> merge = [&](int u, int v) {
        u = find(u);
        v = find(v);

        if (cols[u] > cols[v]) swap(u, v);

        if (--curr_freqs[abs(cols[u])] == 0) curr_freqs.erase(abs(cols[u]));
        if (--curr_freqs[abs(cols[v])] == 0) curr_freqs.erase(abs(cols[v]));


        cols[u] += cols[v];
        cols[v] = u;

        curr_freqs[abs(cols[u])]++;
    };

    for (int row = 0; row < n; row++) {
        for (auto col: eliminations[row]) {
            curr_freqs[1]++;
            cols[col] = -1;
            if (col != 0 && cols[col - 1] != INT_MIN) merge(col, col - 1);
            if (col != n - 1 && cols[col + 1] != INT_MIN) merge(col, col + 1);
        }
        for (auto [v, f]: curr_freqs) freqs[v] += f;
    }

    long long ans = 0;
    while (m > 0) {
        auto [l, f] = *freqs.rbegin(); freqs.erase(prev(freqs.end()));
        //cout << l << " " << f << endl;
        if (m >= l * f) {
            ans += (l - 1) * f;
            m -= l * f;
        } else {
            long long can = m / l;
            ans += (l - 1) * can;
            m -= l * can;
            ans += max(0ll, m - 1);
            m = 0;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}