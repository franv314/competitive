#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, b, c; cin >> n >> b >> c;

    if (b == 0) {
        if (n <= c + 2) {
            return void(cout << n - 1 + (c >= n) << '\n');
        } else {
            return void(cout << "-1\n");
        }
    }

    long long last = (n - c + b - 1) / b;
    long long cnt = max(last, 0LL);

    cout << n - cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}