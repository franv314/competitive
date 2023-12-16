#include <bits/stdc++.h>
using namespace std;

constexpr long long MOD = 998'244'353;

long long fexp(long long base, long long exp) {
    long long ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    }
    return ans;
}

struct Line {
    long long m, q;
    
    Line(long long m, long long q) : m(m), q(q) { }
    Line() : Line(0, 0) { }
    Line operator*(const Line &o) const {
        return {m * o.m % MOD, (m * o.q + q) % MOD};
    }
    Line operator+(const Line &o) const {
        return {(m + o.m) % MOD, (q + o.q) % MOD};
    }
    long long operator()(const long long &v) const {
        return (m * v + q) % MOD;
    }
};

void solve() {
    long long n; cin >> n;

    map<long long, Line> memo;
    memo[1] = {1, 0};
    function<void(long long)> calc = [&](long long sz) {
        Line ways((fexp(2, sz / 2) - 1) * (fexp(2, (sz + 1) / 2) - 1) % MOD, 0);

        if (!memo.count(sz / 2)) calc(sz / 2);
        if (!memo.count((sz + 1) / 2)) calc((sz + 1) / 2);

        Line ways_l = memo[(sz + 1) / 2] * Line(2, 0);
        Line ways_r = memo[sz / 2] * Line(2, 1);

        memo[sz] = ways + ways_l + ways_r;
    };

    calc(n);
    cout << memo[n](1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long t; cin >> t;
    while (t--) solve();
}