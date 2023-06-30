#include <algorithm>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

#define MAXN 200'001

map<int, int> factors[MAXN];

void sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (factors[i].empty()) {
            for (long long p = 1, v = i; v < MAXN; p++, v *= i) {
                for (long long j = v; j < MAXN; j += v) {
                    factors[j][i] = p;
                }
            }
        }
    }
}

int main() {
    sieve();
    
    int n; cin >> n;
    map<int, vector<int>> prime_freq;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        for (auto [p, f]: factors[a]) {
            prime_freq[p].push_back(f);
        }
    }
    
    long long ans = 1;
    for (auto [p, freqs]: prime_freq) {
        if (freqs.size() <= n - 2) continue;
        if (freqs.size() == n - 1) freqs.push_back(0);
        sort(freqs.begin(), freqs.end());
        ans *= powl(p, freqs[1]);
    }
    cout << ans;
}