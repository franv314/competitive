#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> arr(n);
    for (auto &a: arr) {
        cin >> a;
        a--;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        if (arr[i] >= n) continue;
        int start = (i - arr[i] + n) % n;
        int end = (start + arr[i] + 1) % n;
        adj[end].push_back(start);
    }

    vector<int> d(n, -1);
    d[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (auto y: adj[x]) {
            if (d[y] != -1) return void(cout << "Yes\n");
            d[y] = d[x] + 1;
            q.push(y);
        }
    }

    if (*max_element(d.begin(), d.end()) >= k) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}