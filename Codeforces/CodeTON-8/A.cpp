#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;

    if (k != 1 && n != k) return void(cout << "-1\n");

    for (int i = 1; i <= n; i++) cout << (n == k ? 1 : i) << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}