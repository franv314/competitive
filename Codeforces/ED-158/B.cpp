#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i].first;
        heights[i].second = i + 1;
    }

    sort(heights.rbegin(), heights.rend());
    vector<bool> exists(n + 2);
    int cc = 0;
    int ch = 2e9;

    long long tot = 0;

    for (auto [h, i]: heights) {
        tot += (long long)(ch - h) * cc;

        cc += 1 - exists[i - 1] - exists[i + 1];
        exists[i] = true;
    
        ch = h;
    }
    tot += (long long)ch * cc;

    cout << tot - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}