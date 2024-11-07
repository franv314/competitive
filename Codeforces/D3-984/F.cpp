#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 range_xor(i64 N) {
    if (N == 0)
        return 0;
    N--;
    switch (N % 4) {
    case 0: return N;
    case 1: return 1;
    case 2: return N + 1;
    case 3: return 0;
    }
}

void solve() {
    i64 l, r, i, k; cin >> l >> r >> i >> k;
    r++;

    if (i == 0) {
        return void(cout << "0\n");
    }

    i64 l1 = (l >> i) << i;
    i64 r1 = l;

    i64 l2 = r;
    i64 r2 = ((r + (1 << i) - 1) >> i) << i;

    i64 lx = l1 >> i;
    i64 rx = r2 >> i;

    i64 ans = 0;

    // l1-r1
    ans ^= range_xor(l1) ^ range_xor(r1);
    if (r1 % (1 << i) > k)
        ans ^= l1 + k;

    // l2-r2
    ans ^= range_xor(l2) ^ range_xor(r2);
    if (l2 % (1 << i) && l2 % (1 << i) <= k)
        ans ^= r2 - (1 << i) + k;

    // lx-rx
    ans ^= range_xor(lx << i) ^ range_xor(rx << i);
    if ((rx - lx) % 2)
        ans ^= k;
    ans ^= (range_xor(lx) ^ range_xor(rx)) << i;
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
