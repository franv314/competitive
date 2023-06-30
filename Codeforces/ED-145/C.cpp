#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;

        int i;
        for (i = n; i; i--) {
            if (k > i) {
                cout << "1000 ";
                k -= i;
            } else {
                cout << 2 * k - 1 << " ";
                i--;
                break;
            }
        }

        while (i--) cout << "-2 ";

        cout << endl;
    }
}