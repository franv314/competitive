#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;

    for (int i = 0; i < n; i++) {
        if (a[i] != c[i] && b[i] != c[i]) {
            return void(cout << "YES\n");
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}