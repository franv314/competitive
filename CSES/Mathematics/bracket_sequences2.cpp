#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int base, int exp) {
    int ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    }
    return ans;
}

int binom(int n, int m) {
    if (m < 0 || m > n) return 0;
    int ans = 1;
    for (int i = 1; i <= m; i++) {
        ans = (long long)ans * (i + n - m) % MOD * fexp(i, MOD - 2) % MOD;
    }
    return ans;
}

int main() {
    int N; cin >> N;
    string S; cin >> S;
    
    if (N & 1) return cout << 0 << '\n', 0;

    int open = 0, closed = 0;
    for (auto x: S) {
        open += x == '(';
        closed += x == ')';
        if (closed > open) return cout << 0 << '\n', 0;
    }

    cout << (binom(N - open - closed, N / 2 - open) - binom(N - open - closed, N / 2 - open - 1) + MOD) % MOD << '\n';
}