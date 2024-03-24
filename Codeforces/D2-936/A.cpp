#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.begin(), a.end());
    int split = a[(a.size() + 1) / 2 - 1];
    int count_leq = upper_bound(a.begin(), a.end(), split) - a.begin();
    
    cout << count_leq - (a.size() + 1) / 2 + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}