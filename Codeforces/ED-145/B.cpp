#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        long long x; cin >> x;
        long long l = 0, r = INT_MAX;
        while (l + 1 < r) {
            long long m = (l + r) / 2;
            if (m * m < x) l = m;
            else r = m;
        }

        cout << l << "\n";
    }
}