// lamerata

#include <bits/stdc++.h>
using namespace std;

class Array {
    int v1, a, b, c;

    pair<int, int> get(int i) {
        if (i == 0) return {1, 0};

        auto [p, s] = get(i / 2);
        int pow = (long long)p * p % c;
        int ser = (p + 1LL) * s % c;

        if (i & 1) {
            pow = (long long)pow * a % c;
            ser = ((long long)ser * a + 1) % c;
        }

        return {pow, ser};
    }

    friend istream& operator>>(istream&, Array&);
public:

    int operator[](const int &idx) {
        auto [p, s] = get(idx - 1);
        return ((long long)p * v1 + (long long)s * b) % c;
    }
};

istream& operator>>(istream& in, Array &arr) {
    return in >> arr.v1 >> arr.a >> arr.b >> arr.c;
}

#define MAXN 1'000'000

#define STEP 100
#define ECUT 20

int u[MAXN + 1], d[MAXN + 1], m[MAXN + 1]; 
long long dp[MAXN + 1][ECUT];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, E; cin >> N >> E;
    Array U, D, M; cin >> U >> D >> M;

    set<int> xs;

    for (int x = N; x > 0; x /= 2) {
        for (int y = x; y > max(0, x - STEP); y--) {
            xs.insert(y);
            u[y] = U[y];
            d[y] = D[y];
            m[y] = M[y];
        }
    }

    for (auto i: xs) {
        for (int e = 0; e < ECUT; e++) {
            dp[i][e] = 1e18;

            if (i == 1 || xs.count(i - 1)) dp[i][e] = min(dp[i][e], u[i] + dp[i - 1][min(e + 1, ECUT - 1)]);
            if (i == 2 || xs.count(i - 2)) dp[i][e] = min(dp[i][e], d[i] + dp[i - 2][e]);
            if (e > 0)                     dp[i][e] = min(dp[i][e], m[i] + dp[i / 2][e - 1]);
        }
    }

    cout << dp[N][min(E, ECUT - 1)] << '\n';
}