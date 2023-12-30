#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'000
int fact[MAXN];

void precalc() {
    fact[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] + __builtin_ctz(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    precalc();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int f = fact[n - 1] - fact[i] - fact[n - 1 - i];
        if (f == 0) ans ^= a[i];
    }

    cout << ans << '\n';
}