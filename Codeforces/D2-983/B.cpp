#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;

    if (n == 1) {
        return void(cout << "1\n1\n");
    }
    if (k == 1 || k == n) {
        return void(cout << "-1\n");
    }

    if (k % 2 == 0) {
        return void(cout << "3\n1 " << k << " " << k + 1 << "\n");
    } else {
        return void(cout << "3\n1 " << k - 1 << " " << k + 2 << "\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
