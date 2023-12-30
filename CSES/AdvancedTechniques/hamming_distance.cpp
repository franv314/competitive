#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    
    for (auto &x: a) {
        string s; cin >> s;
        for (auto c: s) {
            x *= 2;
            x |= (c - '0');
        }
    }

    int mi = 50;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            mi = min(mi, __builtin_popcount(a[i] ^ a[j]));
        }
    }

    cout << mi << '\n';
}