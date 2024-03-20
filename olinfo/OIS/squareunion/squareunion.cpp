#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> X(N), R(N);
    for (auto &x: X) cin >> x;
    for (auto &x: R) cin >> x;
    
    vector<pair<int, int>> events;
    for (int i = 0; i < N; i++) {
        events.emplace_back(X[i] - R[i], +R[i]);
        events.emplace_back(X[i] + R[i], -R[i]);
    }
    
    sort(events.begin(), events.end());
    multiset<int> active;
    active.insert(0);
    long long ans = 0;
    int last = -1e9;
    
    for (auto [x, upd]: events) {
        ans += 2LL * (x - last) * *active.rbegin();
        if (upd > 0) active.insert(upd);
        else active.erase(active.find(-upd));
        last = x;
    }
    
    cout << ans << '\n';
}