#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long sum(long long l, long long r) {
    return ((r * (r - 1) / 2) % MOD - (l * (l - 1) / 2) % MOD + MOD) % MOD;
}

long long compute(long long n) {
	long long result = 0;
    long long i = 1;
    while (i <= n) {
        long long m = n / i;
        long long r = n % i;
        
        long long d = 1 + r / m;
        result = (result + (m * sum(i % MOD, (i + d) % MOD) % MOD)) % MOD;
        i += d;
    }
    return result;
}

int main() {
    long long n; cin >> n;
    cout << compute(n) << endl;
}