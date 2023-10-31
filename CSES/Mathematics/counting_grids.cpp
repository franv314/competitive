#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

long long fexp(long long b, long long e) {
    long long a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

int main() {
    long long n; cin >> n;

    long long block_size = (n / 2) * ((n + 1) / 2);

    long long one_block = fexp(2, block_size);
    long long two_block = (fexp(2, 2 * block_size) - one_block + MOD) % MOD;
    long long four_block = (fexp(2, 4 * block_size) - one_block - two_block + MOD + MOD) % MOD;

    long long ans = (one_block + two_block * fexp(2, MOD - 2) + four_block * fexp(4, MOD - 2)) % MOD;

    if (n & 1) ans = 2 * ans % MOD;

    cout << ans << '\n';
}