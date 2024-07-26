#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

typedef long long i64;
typedef __gnu_pbds::priority_queue<i64> pairing_heap;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<vector<int>> adj(N);
    vector<int> t(N + M);

    for (int i = 1; i < N + M; i++) {
        int p; cin >> p >> t[i];
        adj[p - 1].push_back(i);
    }

    auto dfs = [&](auto &&dfs, int node) {
        pairing_heap q;
        if (node >= N) {
            q.push(t[node]);
            q.push(t[node]);
            return q;
        }

        for (auto child: adj[node]) {
            pairing_heap cq = dfs(dfs, child);
            q.join(cq);
        }
        for (int i = 0; i < adj[node].size() - 1; i++) q.pop();

        i64 x1 = q.top(); q.pop();
        i64 x0 = q.top(); q.pop();

        q.push(x0 + t[node]);
        q.push(x1 + t[node]);

        return q;
    };

    pairing_heap q = dfs(dfs, 0);
    vector<i64> slope_changes;
    while (!q.empty()) {
        i64 x = q.top(); q.pop();
        slope_changes.push_back(x);
    }
    
    reverse(slope_changes.begin(), slope_changes.end());
    int curr_slope = 1 - (int)slope_changes.size();
    i64 last_point = 0;
    i64 curr_value = accumulate(t.begin(), t.end(), 0LL);
    i64 best_value = curr_value;

    for (auto x: slope_changes) {
        curr_value += curr_slope * (x - last_point);
        best_value = min(best_value, curr_value);

        last_point = x;
        curr_slope++;
    }

    cout << best_value << '\n';
}