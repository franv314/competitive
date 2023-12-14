#include <bits/stdc++.h>
using namespace std;

long long solve(long long n) {
    if (n == 1) return 0;
    if (n == 2) return 12;
    if (n == 3) return 56;
    if (n == 4) return 192;
    return n * n * (n * n - 1)
        - 4 * 2                  // corners
        - 8 * 3                  // near-corners
        - 4 * (n - 4) * 4        // sides
        - 4 * 4                  // inner corners
        - 4 * (n - 4) * 6        // inner sides
        - (n - 4) * (n - 4) * 8; // center
}

int main() {
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        cout << solve(i) / 2 << "\n";
    }
}