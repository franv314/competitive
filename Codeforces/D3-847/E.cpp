#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    
    while (t--) {
        int x; cin >> x;
        int s = x << 1;

        int a = 0, b = 0, carry = 0;

        for (int i = 0; i <= 29; i++) {
            bool sum_has = s & (1 << i);
            bool xor_has = x & (1 << i);

            //cout << sum_has << " " << xor_has << " " << carry << " " << i << endl;

            if (!sum_has && !xor_has && !carry) {
                bool sum_has1 = s & (2 << i);
                bool xor_has1 = x & (2 << i);

                if (sum_has1 != xor_has1) {
                    carry = 1;
                    a |= (1 << i);
                    b |= (1 << i);
                } else {
                    carry = 0;
                }
            } else if (!sum_has && !xor_has && carry) {
                cout << "-1\n";
                goto next;
            } else if (!sum_has && xor_has && !carry) {
                cout << "-1\n";
                goto next;
            } else if (!sum_has && xor_has && carry) {
                a |= (1 << i);
            } else if (sum_has && !xor_has && !carry) {
                cout << "-1\n";
                goto next;
            } else if (sum_has && !xor_has && carry) {
                bool sum_has1 = s & (2 << i);
                bool xor_has1 = x & (2 << i);

                if (sum_has1 != xor_has1) {
                    carry = 1;
                    a |= (1 << i);
                    b |= (1 << i);
                } else {
                    carry = 0;
                }
            } else if (sum_has && xor_has && !carry) {
                a |= (1 << i);
            } else if (sum_has && xor_has && carry) {
                cout << "-1\n";
                goto next;
            }
        }

        cout << a << " " << b << "\n";

        next:;
    }
}
/*

10100
 1010

1101
0111

 */