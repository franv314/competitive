#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr i64 MOD = 1e9 + 7;

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    do {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    } while (e >>= 1);
    return a;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    i64 n; cin >> n;
    cout << fexp(2, n / 2) << '\n';
}
