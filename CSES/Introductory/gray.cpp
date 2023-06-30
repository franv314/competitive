#include <bits/stdc++.h>
using namespace std;

#define MAXN 16

bitset<1 << MAXN> used;

int main() {
    int n; cin >> n;
    int curr = 0;
    
    for (int i = 0; i < (1 << n); i++) {
        for (int i = (1 << (n - 1)); i; i >>= 1) cout << !!(curr & i);
        cout << '\n';
        used.set(curr);

        int change = 1;
        while (used[curr ^ change]) change <<= 1;
        curr ^= change;
    }
}