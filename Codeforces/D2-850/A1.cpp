#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a = 1, b = 0;
        n--;

        for (int d = 2; n; d++) {
            if (d & 2) b += min(d, n);
            else a += min(d, n);
            n -= min(d, n);
        }
        cout << a << " " << b << "\n";
    }
}