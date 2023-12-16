#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b; cin >> a >> b;
    cout << max(a, b) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}