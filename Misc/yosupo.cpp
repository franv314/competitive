#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long fexp(int base, int exp) {
    long long curr = base, ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= curr) %= MOD;
        (curr *= curr) %= MOD;
    }
    return ans;
}

struct LinearFunction {
    long long a, b;

    long long operator()(int x) {
        return (a * x + b) % MOD;
    }
};

LinearFunction operator*(LinearFunction x, LinearFunction y) {
    return {x.a * y.a % MOD, (x.a * y.b + x.b) % MOD};
}

LinearFunction inverse(LinearFunction x) {
    return {fexp(x.a, MOD - 2), (MOD - x.b * fexp(x.a, MOD - 2) % MOD) % MOD};
}

int main() {
    int q; cin >> q;
    deque<LinearFunction> functions;
    LinearFunction function = {1, 0};
    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int a, b; cin >> a >> b;
            functions.push_back({a, b});
            function = functions.back() * function;
        } else if (t == 1) {
            LinearFunction rem = functions.front(); functions.pop_front();
            function = function * inverse(rem);
        } else {
            int x; cin >> x;
            cout << function(x) << '\n';
        }
    }
}