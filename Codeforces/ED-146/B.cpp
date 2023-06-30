#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        
        int best = INT_MAX;
        for (int i = 1; i <= 1e6; i++) {
            best = min(best, i - 1 + (a + i - 1) / i + (b + i - 1) / i);
        }
        cout << best << "\n";
    }
}