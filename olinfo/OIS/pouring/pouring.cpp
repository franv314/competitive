#include <bits/stdc++.h>
using namespace std;

array<long long, 3> extended_euclid(int n, int m) {
    if (m == 0) {
        return {n, 1, 0};
    }
    auto [gcd, k_0, k_1] = extended_euclid(m, n % m);
    return {gcd, k_1, k_0 - (n / m) * k_1};
}

int main() {
    long long A_C, B_C; cin >> A_C >> B_C;
    long long A_S, B_S; cin >> A_S >> B_S;
    long long A_G, B_G; cin >> A_G >> B_G;

    assert(A_S == 0 && B_S == 0);

    auto [gcd, k_0, k_1] = extended_euclid(A_C, B_C);
    assert((A_G + B_G) % gcd == 0);
}