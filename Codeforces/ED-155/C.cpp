#include <bits/stdc++.h>
using namespace std;

#define MAXS 200'000

constexpr int MOD = 998244353;
int fact[MAXS + 1];

void precalc() {
    fact[0] = 1;
    for (int i = 1; i <= MAXS; i++) {
        fact[i] = (long long)fact[i - 1] * i % MOD;   
    }
}

void solve() {
    string s; cin >> s;
    int n = s.size();
    s.push_back('#');
    
    int ways = 1;
    int shortest = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (s[r] != s[r + 1]) {
            shortest += r - l;
            if (r != l) {
                ways = (long long)ways * (r - l + 1) % MOD;
            }
            
            l = r + 1;
        } 
    }
    
    ways = (long long)ways * fact[shortest] % MOD;
    
    cout << shortest << ' ' << ways << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    precalc();
    int t; cin >> t;
    while (t--) solve();
}