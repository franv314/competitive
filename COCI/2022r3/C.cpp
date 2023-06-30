#include <bits/stdc++.h>
using namespace std;

/*void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(m), b(m), w(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> w[i];
        a[i]--, b[i]--;
    }

    long long min_dst;
    {
        vector<tuple<int, int, int>> adj[n];
        for (int i = 0; i < m; i++) {
            adj[a[i]].push_back({i, b[i], w[i]});
            adj[b[i]].push_back({i, a[i], w[i]});
        }

        vector<bool> visited(n);
        vector<long long> dst(n, 1e18);
        priority_queue<pair<long long, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            auto [dist, node] = q.top(); q.pop();
            if (visited[node]) continue;

            visited[node] = true;
            dist *= -1;
            if (node == n - 1) {
                min_dst = dist;
            }
            for (auto [i, n, w]: adj[node]) {
                if (dist + w < dst[n]) {
                    dst[n] = dist + w;
                    q.push({-dst[n], n});
                }
            }
        }
    }
    vector<int> remove;
    for (int i = 0; i < m; i++) {
        w[i] += 2;

        vector<tuple<int, int, int>> adj[n];
        for (int i = 0; i < m; i++) {
            adj[a[i]].push_back({i, b[i], w[i]});
            adj[b[i]].push_back({i, a[i], w[i]});
        }

        vector<bool> visited(n);
        vector<long long> dst(n, 1e18);
        priority_queue<pair<long long, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            auto [dist, node] = q.top(); q.pop();
            if (visited[node]) continue;

            visited[node] = true;
            dist *= -1;
            if (node == n - 1) {
                if (dist == min_dst + 1) {
                    remove.push_back(i);
                }
                break;
            }
            for (auto [i, n, w]: adj[node]) {
                if (dist + w < dst[n]) {
                    dst[n] = dist + w;
                    q.push({-dst[n], n});
                }
            }
        }

        w[i] -= 2;
    }

    cout << remove.size() << "\n";
    for (auto x: remove) cout << x + 1 << " ";
    cout << endl;
}*/

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(m), b(m), w(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> w[i];
        a[i]--, b[i]--;
    }

    vector<tuple<int, int, int>> adj[n];
    for (int i = 0; i < m; i++) {
        adj[a[i]].push_back({i, b[i], w[i]});
        adj[b[i]].push_back({i, a[i], w[i]});
    }

    vector<bool> visited(n);
    vector<long long> dst(n, 1e18);
    priority_queue<pair<long long, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [dist, node] = q.top(); q.pop();
        if (visited[node]) continue;

        visited[node] = true;
        dist *= -1;
        if (node == n - 1) {
            break;
        }
        for (auto [i, n, w]: adj[node]) {
            if (dist + w < dst[n]) {
                dst[n] = dist + w;
                q.push({-dst[n], n});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}