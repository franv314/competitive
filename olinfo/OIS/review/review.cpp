#include <bits/stdc++.h>
using namespace std;

int pows[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

long long fexp(long long b, long long e, long long m) {
    long long a = 1;
    for (; e; e >>= 1) {
        if (e & 1) (a *= b) %= m;
        (b *= b) %= m;
    }
    return a;
}

int solve(int k, int g, int m, long long a) {
    if (a > m) return INT_MAX;

    int ans = k * g;
    for (auto d: {2, 5})
        if (g % d == 0)
            ans = min(ans, solve(k, g / d, m, d * a));
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N, M, D; cin >> N >> M >> D;
    vector<int> A(N);
    for (auto &a: A) cin >> a;

    if (count(A.begin(), A.end(), 0) == N) {
        cout << 0 << '\n';
        return 0;
    }

    int g = accumulate(A.begin(), A.end(), pows[D], gcd<int, int>);
    int m = pows[D] / g;
    transform(A.begin(), A.end(), A.begin(), [&](int x) {return x / g; });

    int phi = 0;
    for (int i = 1; i <= m; i++) phi += gcd(i, m) == 1;

    for (int i = 1; i < m; i++) {
        if (gcd(i, m) != 1) continue;
        int inv = fexp(i, phi - 1, m);

        int old = 0;
        int cnt = 0;
        for (auto a: A) {
            int val = (long long)a * inv % m;
            if (val == 0) val = m;
            cnt += (val <= old);
            old = val;
        }
        if ((long long)cnt * m + old <= M) {
            cout << solve(i, g, M, (long long)cnt * m + old) << '\n';
            return 0;
        }
    }
}