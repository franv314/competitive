#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    
    long long A = accumulate(a.begin(), a.end(), 0ll);
    long long B = accumulate(b.begin(), b.end(), 0ll);
    if (A > B) cout << "Tsondu\n";
    if (A == B) cout << "Draw\n";
    if (A < B) cout << "Tenzing\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}