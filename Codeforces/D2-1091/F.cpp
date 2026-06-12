#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr int MAXB = 20;

i64 count_xor(int maxsum, int x) {
    int sb = __builtin_popcount(x);
    maxsum -= x;

    if (maxsum < 0) return 0;

    maxsum /= 2;

    i64 count = 0;
    for (int b = MAXB; b >= 0; b--) {
        if (x & (1 << b)) continue;
    
        if (maxsum >= (1 << b)) {
            int mask = (~x) & ((1 << b) - 1);
            count += 1 << __builtin_popcount(mask);
            maxsum -= (1 << b);
        }
    }
    count++;
    count <<= sb;

    return count;
}

void solve() {
    int x1, x2; cin >> x1 >> x2;
    x1--;
    x2--;

    if (x1 == 0) {
        cout << "1 1\n";
        return;
    }

    pair<int, int> mi = {1e9, -1};
    for (int i = 0; i <= x1; i++) {
        mi = min(mi, {count_xor(x2, i), i});
    }

    int lim = 1 << (31 - __builtin_clz(x1));
    if (mi.second >= lim) {
        cout << 1 + lim << " " << x1 + 1 - (mi.second - lim) << '\n';
    } else {
        cout << 1 << " " << x1 + 1 - mi.second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);


    int t; cin >> t;
    while (t--) solve();
}
