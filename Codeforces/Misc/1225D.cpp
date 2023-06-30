#include <bits/stdc++.h>
using namespace std;

#define PRIMES 100'001
#define MAXN 100'000

const int MOD = 1e9 + 7;

hash<bitset<PRIMES>> hasher;

long long solve2(int n, vector<int> a) {    
    unordered_map<int, int> cnt;
    long long total = 0;
    for (auto x: a) {
        bitset<PRIMES> pp;
        int nx = x;
        for (int j = 2; j * j <= nx; j++) {
            while (x % j == 0) {
                pp.flip(j);
                x /= j;
            }
        }
        if (x != 1) pp.flip(x);
        total += cnt[hasher(pp)];
        cnt[hasher(pp)]++;
    }
    return total;
}

long long solve(int n, int k, vector<int> a) {
    vector<long long> p;
    for (int i = 1; powl(i, k) <= 1e10; i++) {
        p.push_back(powl(i, k));
    }
    
    long long total = 0;
    
    map<int, int> freqs;
    for (auto x: a) {
        for (auto v: p) {
            if (v % x) continue;
            total += freqs[v / x];
        }
        freqs[x]++;
    }
    return total;
}

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    if (k == 2) cout << solve2(n, a);
    else cout << solve(n, k, a);
}