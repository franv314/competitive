#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i = 0; i < n / 2; i++) {
            cout << n - i << " "
                 << i + 1 << " ";
        }
        if (n & 1)
            cout << 1 + n / 2;
        cout << endl;
    }
}