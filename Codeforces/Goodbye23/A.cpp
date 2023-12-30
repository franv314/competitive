#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    long long val = 1;
    for (int i = 0; i < n; i++) {
        long long x; cin >> x;
        val *= x;
    }

    if (2023 % val) return void(cout << "NO\n");
    cout << "YES\n";
    cout << 2023 / val << ' ';
    for (int i = 1; i < k; i++) cout << 1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}