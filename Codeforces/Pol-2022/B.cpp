#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        
        int ma = n / k;
        int ex = n % k;

        for (int i = 0; i < m; i++) {
            int am; cin >> am;
            if (am == ma + 1) {
                if (--ex < 0) {
                    cout << "NO\n";
                    goto next;
                }
            }
            if (am > ma + 1) {
                cout << "NO\n";
                goto next;
            }
        }
        cout << "YES\n";
        next:;
    }
}