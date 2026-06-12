#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> p(n), d(n);
    for (auto &x: p) cin >> x;
    for (auto &x: d) cin >> x;

    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        vector<int> dom_idx;
        for (int j = i + 1; j < n; j++)
            if (p[j] > p[i])
                dom_idx.push_back(j);

        if (dom_idx.size() < d[i])
            return void(cout << "-1\n");
        
        if (d[i] == 0) {
            ans[i] = n - i;
            continue;
        }

        vector<int> vals;
        for (auto x: dom_idx)
            vals.push_back(ans[x]);
        
        int pos = dom_idx.size() - d[i];
        nth_element(vals.begin(), vals.begin() + pos, vals.end());

        int val = vals[pos];
        ans[i] = val;

        for (int j = i + 1; j < n; j++)
            if (ans[j] >= val)
                ans[j]++;
    }

    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
