#include <bits/stdc++.h>
using namespace std;

#define MAXV 200001

const int MOD = 1e9 + 7;

long long fexp(long long base, int exp) {
    long long ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= base) %= MOD;
        (base *= base) %= MOD;
    }
    return ans;
}

int main() {
    int K; cin >> K;
    vector<int> V(K);
    for (auto &v: V) cin >> v;
    
    vector<long long> factorials(MAXV + 1, 1);
    vector<long long> inv(MAXV + 1, 1);
    for (int i = 1; i <= MAXV; i++) {
        factorials[i] = i * factorials[i - 1] % MOD;
        inv[i] = fexp(factorials[i], MOD - 2);
    }
    
    vector<int> old_ways(K), new_ways(K), temp(K);
    old_ways[0] = 1;
    for (int i = 1; i <= K; i++) {
        int amount = V[i - 1];
        fill(temp.begin(), temp.end(), 0);
        fill(new_ways.begin(), new_ways.end(), 0);
        
        for (int cnt = 0; cnt <= amount; cnt++) {
            int val = (long long)cnt * i % K;
            long long ways = factorials[amount] * inv[cnt] % MOD * inv[amount - cnt] % MOD;
            (temp[val] += ways) %= MOD;
        }
        
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                (new_ways[(j + k) % K] += old_ways[j] * (long long)temp[k] % MOD) %= MOD;
            }
        }
        swap(new_ways, old_ways);
    }
    cout << old_ways[0];
}