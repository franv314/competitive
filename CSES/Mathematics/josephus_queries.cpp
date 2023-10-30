#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k) {
    if (k < n / 2) {
        return 1 + 2 * k;
    }
    if ((n & 1) && k == n / 2) {
        return 0;
    }

    int x = solve(n / 2, k - (n + 1) / 2);

    if (n & 1) {
        return 2 * x + 2;
    } else {
        return 2 * x;
    }
}

int main() {
    int q; cin >> q;

    while (q--) {
        int n, k; cin >> n >> k;
        cout << 1 + solve(n, k - 1) << '\n';
    }
}