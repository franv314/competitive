#include <bits/stdc++.h>
using namespace std;

unordered_set<long long> vals;
typedef __int128_t lll;

void precalc() {
    for (long long k = 2; k <= 1e6; k++) {
        lll last = k * k;
        lll curr = 1 + k + k * k;
        while (curr + last * k <= 1e18) {
            last *= k;
            curr += last;
            vals.insert(curr);
        }
    }
}

void solve() {
    long long val; cin >> val;
    if (vals.count(val)) return void(cout << "YES\n");
    
    long long l = 2, r = 1e9 + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (1 + m + m * m <= val) l = m;
        else r = m;
    }
    if (1 + l + l * l == val) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    precalc();
    int t; cin >> t;
    while (t--) solve();
}