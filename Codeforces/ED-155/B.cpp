#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    
    cout << min(
        accumulate(a.begin(), a.end(), 0LL) + (long long)n * *min_element(b.begin(), b.end()), 
        accumulate(b.begin(), b.end(), 0LL) + (long long)n * *min_element(a.begin(), a.end())
    ) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}