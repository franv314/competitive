#include <bits/stdc++.h>
#include <queue>
using namespace std;

int to_int(string s) {
    int ans = 0;
    for (auto x: s) {
        ans *= 2;
        if (x == '1') ans += 1;
    }
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    int start = 0;
    string s; cin >> s;
    start = to_int(s);
    
    vector<tuple<int, int, int>> medicines(m);
    for (auto &[d, cures, gives]: medicines) {
        cin >> d;
        string a; cin >> a;
        string b; cin >> b;
        cures = to_int(a);
        gives = to_int(b);
    }
    
    vector<long long> dst(1 << n, 1e18);
    vector<bool> visited(1 << n, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    
    dst[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (n == 0) return void(cout << d << '\n');
        if (visited[n]) continue;
        
        for (auto [days, cures, gives]: medicines) {
            int new_s = n;
            new_s &= ~cures;
            new_s |= gives;
            if (d + days < dst[new_s]) {
                dst[new_s] = d + days;
                q.push({dst[new_s], new_s});
            }
        }
    }
    cout << "-1\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}