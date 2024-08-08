#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, int> freq;
    for (auto x: a) freq[x]++;

    for (auto [_, f]: freq)
        if (f & 1)
            return void(cout << "YES\n");
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}