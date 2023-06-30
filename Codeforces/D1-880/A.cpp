#include <bits/stdc++.h>
using namespace std;

int powers[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

void solve() {
    int A, B, C; cin >> A >> B >> C;
    long long k; cin >> k;
    
    int min_a = powers[A - 1];
    int max_a = powers[A];
    
    int min_b = powers[B - 1];
    int max_b = powers[B];
    
    int min_c = powers[C - 1];
    int max_c = powers[C];
    
    long long curr = 0;
    
    for (int a = min_a; a < max_a; a++) {
        int min_add = max(min_c - a, min_b);
        int max_add = min(max_c - a, max_b);
        
        int range_len = max_add - min_add;
        if (range_len <= 0) continue;
        if (curr + range_len >= k) {
            int idx = k - curr - 1;
            cout << a << " + " << min_add + idx << " = " << a + min_add + idx << "\n";
            return;
        }
        
        curr += range_len;
    }
    cout << "-1\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}