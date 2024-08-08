#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef priority_queue<pair<int, i64>, vector<pair<int, i64>>, greater<>> pq;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int> p(n - 1);
    for (auto &x: p) cin >> x;
    p.insert(p.begin(), -1);

    vector<vector<int>> children(n);
    for (int i = 1; i < n; i++) {
        children[p[i] - 1].push_back(i);
    }

    auto dfs = [&](auto &&dfs, int node, int d = 0) -> pair<i64, pq> {
        if (children[node].empty()) {
            pq q;
            q.emplace(d, 1e18);
            return {0, q};
        }

        long long children_sum = 0;
        long long ans = 0;
        pq q;
        for (auto child: children[node]) {
            auto [c_ans, c_q] = dfs(dfs, child, d + 1);
            ans += c_ans;
            while (!c_q.empty()) {
                q.push(c_q.top());
                c_q.pop();
            }

            children_sum += a[child];
        }
        
        if (children_sum >= a[node]) {
            q.emplace(d, children_sum - a[node]);
            return {ans, q};
        }

        while (a[node] > children_sum) {
            auto [dd, space] = q.top(); q.pop();

            if (space < a[node] - children_sum) {
                children_sum += space;
                ans += space * (dd - d);
            } else {
                space -= a[node] - children_sum;
                ans += (long long)(a[node] - children_sum) * (dd - d);
                children_sum = a[node];
                q.emplace(dd, space);
            }
        }

        return {ans, q};
    };

    cout << dfs(dfs, 0).first << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}