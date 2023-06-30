#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long fexp(int base, int exp) {
    long long ans = 1, curr = base;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= curr) %= MOD;
        (curr *= curr) %= MOD;
    }
    return ans;
}

int main() {
    int n; cin >> n;
    vector<vector<int>> gifts(n);
    vector<int> cnt(1e6 + 1);
    
    for (auto &child: gifts) {
        int k; cin >> k;
        child.resize(k);
        for (auto &x: child) {
            cin >> x;
            cnt[x]++;
        }
    }
    
    long long total = 0;
    long long prob = fexp(n, MOD - 2);
    for (auto child: gifts) {
        long long prob2 = fexp(child.size(), MOD - 2);
        for (auto gift: child) {
            long long prob3 = cnt[gift] * fexp(n, MOD - 2) % MOD;
            (prob3 *= prob2) %= MOD;
            (prob3 *= prob) %= MOD;
            (total += prob3) %= MOD;
        }
        
    }
    cout << total;
}