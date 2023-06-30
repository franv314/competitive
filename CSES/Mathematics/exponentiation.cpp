#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(int b, int e) {
    if (e == 0) return 1;

    long long temp = power(b, e / 2);
    if (e & 1) return temp * temp % MOD * b % MOD;
    return temp * temp % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    while (n--) {
        int b, e; cin >> b >> e;
        cout << power(b, e) << endl;
    }
}