#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        long long n, k; cin >> n >> k;
        if (k % 2 == 0) {
            cout << (n % 2 == 0 ? "YES\n" : "NO\n");
        } else {
            if (n % 2 == 0) cout << "YES\n";
            else if (n < k) cout << "NO\n";
            else cout << "YES\n";
        }
    }
}