#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int x = 0;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        if (i & 1) x ^= p;
    }
    cout << (x ? "first\n" : "second\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}