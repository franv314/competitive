#include <bits/stdc++.h>
using namespace std;

#define int long long

int x[4] = {0, 1, 3, 0};

main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int Q; cin >> Q;
    while (Q--) {
        int N; cin >> N;
        
        int X = x[N & 3];
        for (int mod = 8; mod <= (1ll << 40); mod *= 2) {
            int m = N & (mod - 1);
            if (m >= mod / 2 && m % 2 == 0) {
                X += mod / 2;
            }
        }
        
        int ma = 0;
        for (int mask = 1ll << 40; mask; mask >>= 1) {
            if (!(X & mask) && (ma | mask) <= N) {
                ma |= mask;
            }
        }
        
        cout << X << " " << (X ^ ma) << "\n";
    }
}