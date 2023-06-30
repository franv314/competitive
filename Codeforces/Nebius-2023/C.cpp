#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, x, p; cin >> n >> x >> p;
        int needed = (n - x) % n;

        for (long long f = 1; f <= min(2 * n, p); f++) {
            long long spin = (f * (f + 1) / 2) % n;
            if (spin == needed) {
                cout << "Yes\n";
                goto next;
            }
        }   

        cout << "No\n";
        next:;
    }
}