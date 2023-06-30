#include <bits/stdc++.h>
using namespace std;

constexpr int cfr = 7 * 19 * 23 * 25 * 27 * 29 * 31;
constexpr int mods[] = {7, 19, 23, 25, 27, 29, 31};

tuple<int, int, int> extended_euclid(int a, int b) {
    if (b == 0) return {a, 1, 0};
    
    auto [g, c_a, c_b] = extended_euclid(b, a % b);
    return {g, c_b, c_a - a / b * c_b};
}

void solve() {
    unordered_map<int, int> rems;
    for (int a = 1; a <= 30; a++) {
        int b = cfr + a;
        cout << "? " << a << " " << b << endl;

        int gcd; cin >> gcd;
        for (auto mod: mods) {
            if (gcd % mod == 0) {
                rems[mod] = (cfr - a) % mod;
            }
        }
    }

    int m1 = 1, a1 = 0;

    for (auto m2: mods) {
        auto [_, n1, n2] = extended_euclid(m1, m2);
        int a2 = rems[m2];

        n1 = (n1 + cfr) % cfr;
        n2 = (n2 + cfr) % cfr;

        a1 = ((long long)n1 * m1 % cfr * a2 % cfr + (long long)n2 * m2 % cfr * a1 % cfr) % cfr;
        m1 *= m2;
    }
    cout << "! " << a1 << endl;
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}