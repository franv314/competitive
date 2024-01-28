#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 999999893;

int fexp(int b, int e) {
    int ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    }
    return ans;
}

struct Sqrt2 {
    int A, B;

    Sqrt2(int A, int B) : A(A), B(B) { }

    Sqrt2 operator+(const Sqrt2 &o) const { return Sqrt2((A + o.A) % MOD, (B + o.B) % MOD); }
    Sqrt2 operator-() const { return Sqrt2((MOD - A) % MOD, (MOD - B) % MOD); }
    Sqrt2 operator-(const Sqrt2 &o) const { return (*this) + (-o); }
    Sqrt2 operator*(const Sqrt2 &o) const {
        int nA = ((long long)A * o.A + 2LL * B * o.B) % MOD;
        int nB = ((long long)B * o.A + (long long)A * o.B) % MOD;
        return Sqrt2(nA, nB);
    }
    Sqrt2 operator/(const Sqrt2 &o) const {
        auto [num_A, num_B] = (*this) * Sqrt2(o.A, (MOD - o.B) % MOD);
        long long den = (((long long)o.A * o.A % MOD) - (2LL * o.B * o.B % MOD) + MOD) % MOD;
        return Sqrt2((long long)num_A * fexp(den, MOD - 2) % MOD, (long long)num_B * fexp(den, MOD - 2) % MOD);
    }
};

Sqrt2 fexp(Sqrt2 b, int e) {
    Sqrt2 ans(1, 0);
    for (; e; e >>= 1) {
        if (e & 1) ans = ans * b;
        b = b * b;
    }
    return ans;
}

void solve() {
    int N; cin >> N;

    Sqrt2 series = (fexp(Sqrt2(0, 1), N + 1) - Sqrt2(1, 0)) / Sqrt2(MOD - 1, 1);

    Sqrt2 A = series - Sqrt2(1, MOD - 1);
    Sqrt2 B = series - Sqrt2(1, 1);

    Sqrt2 R = B / A;

    cout << R.B << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}