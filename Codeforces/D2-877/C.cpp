#include <bits/stdc++.h>
using namespace std;

bool prime(int i) {
    for (int j = 2; j < i; j++)
        if (i % j == 0) return false;
    return true;
}

void solve() {
    int n, m; cin >> n >> m;
    if (prime(m) && prime(n)) {
        int k = 2;
        while (n % k == 0) k++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << 1 + (k * i * m + j) % (n * m) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    } else if (!prime(m)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << 1 + (i * m + j) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    } else {
        assert(!prime(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << 1 + (j * n + i) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    // ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}