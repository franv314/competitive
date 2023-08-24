#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, d; cin >> n >> m >> d;

    priority_queue<int, vector<int>, greater<int>> pq;
    int64_t total = 0;
    int64_t ma = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        
        if (x < 0) continue;
        if (pq.size() < m) {
            total += x;
            pq.push(x);
        } else if (pq.top() < x) {
            total -= pq.top(); pq.pop();
            total += x;
            pq.push(x);
        }
        ma = max(ma, total - (int64_t)d * (i + 1));
    }
    cout << ma << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}