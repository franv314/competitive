#include <bits/stdc++.h>
using namespace std;

#define MAXN 20'000'001

int primes[MAXN];

void sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (primes[i] == 0) {
            for (int j = i; j < MAXN; j += i) {
                primes[j]++;
            }
        }
    }
}

void solve() {
    int c, d, x; cin >> c >> d >> x;
    vector<int> divisors;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            divisors.push_back(i);
            if (i * i != x) divisors.push_back(x / i);
        }
    }
    
    long long total = 0;
    for (auto G: divisors) {
        if ((x + (long long)d * G) % c != 0) continue;
        long long L = (x + (long long)d * G) / c;
        
        if (L % G != 0) continue;
        long long add = 1 << primes[L / G];
        total += add;
    }
    cout << total << '\n';
}

int main() {
    sieve();
    int t; cin >> t;
    while (t--) solve();
}