#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    vector<int> left(n + 1);
    vector<int> min_left(n + 1, INT_MAX);
    pair<int, int> scheduled = {a.back(), 0};
    
    for (int i = n - 1; i >= 0; i--) {
        left[i] = min(left[i + 1] + 1, min_left[a[i]]);
        
        min_left[scheduled.first] = min(min_left[scheduled.first], scheduled.second);
        scheduled = {a[i - 1], left[i]};
    }
    cout << n - left[0] << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}