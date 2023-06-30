#include <bits/stdc++.h>
using namespace std;

long long pow(int b, int e) {
    long long ans = 1;
    for (int i = 0; i < e; i++) ans *= b;
    return ans;
}

long long eval(int x, int y) {
    return y * pow(x, y) + x * pow(y, x);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n & 1) {
            cout << -1 << "\n";
        } else {
            assert(eval(1, n / 2) == n);
            cout << 1 << " " << n / 2 << "\n";
        }
        out:;
    }
}