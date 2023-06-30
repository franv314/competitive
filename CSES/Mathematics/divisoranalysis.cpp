#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long fexp(long long base, int exp) {
    long long curr = base, ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= curr) %= MOD;
        (curr *= curr) %= MOD;
    }
    return ans;
}

int main() {
    int n; cin >> n;
    vector<pair<int, int>> primes(n);
    for (auto &[prime, power]: primes) cin >> prime >> power;
    
    long long divisors = 1, divisor_sum = 1;
    for (auto [prime, power]: primes) {
        (divisors *= (power + 1)) %= MOD;
        
        long long f = ((fexp(prime, power + 1) - 1 + MOD) % MOD) * fexp((prime - 1 + MOD) % MOD, MOD - 2) % MOD;
        (divisor_sum *= f) %= MOD;
    }
    
    vector<long long> prefix(n + 1, 1), suffix(n + 1, 1);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] * (primes[i].second + 1) % (MOD - 1);
    for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] * (primes[i].second + 1) % (MOD - 1);
    
    long long divisors_prod = 1;
    for (int i = 0; i < n; i++) {
        auto [prime, power] = primes[i];
        long long others = prefix[i] * suffix[i + 1] % (MOD - 1);
        long long me = ((long long)power * (power + 1) / 2) % (MOD - 1);
        long long p = others * me % (MOD - 1);
        long long f = fexp(prime, p);
        (divisors_prod *= f) %= MOD;
    }
    
    cout << divisors << ' ' << divisor_sum << ' ' << divisors_prod;
}