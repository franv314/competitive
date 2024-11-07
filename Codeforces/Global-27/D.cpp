#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;
typedef long double f80;

struct BigInt {
    int odd, exp;

    long long operator()() {
        long long ans = 1, base = 2;
        for (int e = exp; e; e >>= 1) {
            if (e & 1) ans = ans * base % MOD;
            base = base * base % MOD;
        }
        return ans * odd % MOD;
    }

    BigInt d(int f) {
        BigInt ans = *this;
        ans.exp += f;
        return ans;
    }

    BigInt() { }
    BigInt(int x) : odd(x), exp(0) {
        while (odd % 2 == 0) {
            exp++;
            odd /= 2;
        }
    }
};

strong_ordering operator<=>(const BigInt &u, const BigInt &v) {
    if (v.exp - u.exp >= 30) return strong_ordering::less;
    if (u.exp - v.exp >= 30) return strong_ordering::greater;

    if (u.exp > v.exp) {
        long long ru = (long long)u.odd << (u.exp - v.exp);
        long long rv = (long long)v.odd;
        return ru <=> rv;
    } else {
        long long ru = (long long)u.odd;
        long long rv = (long long)v.odd << (v.exp - u.exp);
        return ru <=> rv;
    }
}

void solve() {
    int n; cin >> n;
    vector<BigInt> a(n);
    for (auto &x: a) {
        int v; cin >> v;
        x = BigInt(v);
    }

    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, greater<>> q;
    long long sum = 0;

    for (auto curr: a) {
        BigInt orig = curr;
        while (!q.empty() && q.top().second < curr.d(q.top().second.exp)) {
            BigInt t = q.top().second; q.pop();
            (sum += MOD - t()) %= MOD;
            
            curr.exp += t.exp;
            t.exp = 0;

            (sum += t()) %= MOD;
        }

        (sum += curr()) %= MOD;
        q.push({orig, curr});

        cout << sum << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}