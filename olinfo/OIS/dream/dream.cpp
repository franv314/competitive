// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define int long long

const int MOD = 666'013;

signed main() {
	int K, X;
    cin >> K >> X;

    vector<long long> pow10(X + 1);
    pow10[0] = 1;
    for (int i = 1; i <= X; i++) pow10[i] = (pow10[i - 1] * 10) % MOD;
    long long base = (pow10[X - 1] + 1) % MOD;
    long long total = 0;
    
    for (int k = 0; k < K; k++) {
        total = (total + base) % MOD;
        int i = 0;
        for (int kk = k; kk; kk /= 10) {
            int last_cifra = kk % 10;
            total = (total + (last_cifra * pow10[X / 2 + i]) + (last_cifra * pow10[X / 2 - i - 1])) % MOD;
            i++;
        }
    }

    cout << total << endl; // print the result
    return 0;
}