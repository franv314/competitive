#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    if (k > 3) return void(cout << "0\n");
    if (k == 1) return void(cout << "1\n");

    int twos = min(n - 1, m) + m / n;
    int threes = m - twos;

    if (k == 2) cout << twos << '\n';
    else cout << threes << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}