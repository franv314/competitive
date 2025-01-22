#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

constexpr int MAXK = 1e5;
constexpr int MAXP = 50;
constexpr int MOD = 998244353;
vector<i64> fact(MAXP), invs(MAXP);
vector<vector<int>> divisors(MAXK + 1);

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    do {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    } while (e >>= 1);
    return a;
}

void precalc() {
    for (int i = 2; i <= MAXK; i++)
        for (int j = i; j <= MAXK; j += i)
            divisors[j].push_back(i);
    
    fact[0] = invs[0] = 1;
    for (int i = 1; i < MAXP; i++) {
        fact[i] = i * fact[i - 1] % MOD;
        invs[i] = fexp(fact[i], MOD - 2);
    }
}

void solve() {
    int k, n; cin >> k >> n;

    vector<i64> bin(k + 1);
    bin[0] = 1;
    for (int i = 1; i <= k; i++) {
        bin[i] = bin[i - 1] * (n - i + 2) % MOD * fexp(i, MOD - 2) % MOD;
    }

    auto rec = [&](auto &&rec, int num, int rem, int cur, int streak, int len, i64 streak_acc) -> i64 {
        if (len > n)
            return 0;
        if (rem == 1) {
            streak_acc = streak_acc * invs[streak] % MOD;
            i64 perms = fact[len] * streak_acc % MOD;
            i64 effective = perms * bin[len + 1] % MOD;
            if (len == 0)
                effective = (effective + MOD - 1) % MOD;
            return effective;
        }

        i64 ans = 0;
        if (cur != -1 && rem % divisors[num][cur] == 0)
            ans += rec(rec, num, rem / divisors[num][cur], cur, streak + 1, len + 1, streak_acc);
    
        (streak_acc *= invs[streak]) %= MOD;
        for (int i = cur + 1; i < divisors[num].size(); i++) {
            if (rem % divisors[num][i] != 0)
                continue;
            
            ans += rec(rec, num, rem / divisors[num][i], i, 1, len + 1, streak_acc);
            ans %= MOD;
        }

        return ans;
    };

    for (int i = 1; i <= k; i++)
        cout << rec(rec, i, i, -1, 0, 0, 1) << ' ';

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    precalc();
    int t; cin >> t;
    while (t--) solve();
}
