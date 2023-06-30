#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(int b, int e, int mod) {
    if (e == 0) return 1;

    long long temp = power(b, e / 2, mod);
    if (e & 1) return temp * temp % mod * b % mod;
    return temp * temp % mod;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    while (n--) {
        int a, b, c; cin >> a >> b >> c;
        cout << power(a, power(b, c, MOD - 1), MOD) << endl;
    }
}