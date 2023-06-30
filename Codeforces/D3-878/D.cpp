#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<long long> a(n);
    for (auto &x: a) cin >> x;
    sort(a.begin(), a.end());
    a.push_back(LLONG_MAX);
    a.push_back(LLONG_MAX);
    a.push_back(LLONG_MAX);
    
    int l = -1, r = 1'000'000'000;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        int i = 0;
        int b_1 = a[i];
        while (a[++i] <= b_1 + 2 * m);
        int b_2 = a[i];
        while (a[++i] <= b_2 + 2 * m);
        int b_3 = a[i];
        while (a[++i] <= b_3 + 2 * m);
        
        if (i >= n) r = m;
        else l = m;
    }
    cout << l + 1 << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}