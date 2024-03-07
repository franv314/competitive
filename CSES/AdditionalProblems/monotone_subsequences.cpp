#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    if (k * k < n) return void(cout << "IMPOSSIBLE\n");

    for (int i = 0; i < n; i += k) {
        for (int j = min(i + k, n) - 1; j >= i; j--) {
            cout << j + 1 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}