#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long fexp(long long base, long long exp) {
    long long curr = base, ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= curr) %= MOD;
        (curr *= curr) %= MOD;
    }
    return ans;
}

int main() {
    string s; cin >> s;
    vector<int> freq(26);
    
    for (auto c: s) freq[c - 'a']++;
    long long ans = 1;
    for (int i = 1; i <= s.size(); i++) {
        (ans *= i) %= MOD;
    }
    for (auto f: freq) {
        for (int i = 1; i <= f; i++) {
            (ans *= fexp(i, MOD - 2)) %= MOD;
        }
    }
    cout << ans;
}