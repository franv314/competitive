#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

struct Fenwick {
    vector<int> arr;

    void add(int x, int d) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += d;
    }

    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    int query(int l, int r) {
        return query(r - 1) - query(l - 1);
    }

    Fenwick(int size) : arr(size + 1) { }
};

long long fexp(long long b, long long e) {
    long long ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = ans * b % MOD;
        b = b * b % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M, K; cin >> N >> M >> K;
    
    vector<int> fact(2'100'001), inv_fact(2'100'001);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++)
        fact[i] = (long long)fact[i - 1] * i % MOD;
    inv_fact.back() = fexp(fact.back(), MOD - 2);
    for (int i = fact.size() - 2; i >= 0; i--)
        inv_fact[i] = (long long)inv_fact[i + 1] * (i + 1) % MOD;

    vector<int> V(N + 1);
    Fenwick fenwick(N);
    for (int i = 1; i <= N; i++) {
        cin >> V[i];
        V[i] = max(V[i], K);
        fenwick.add(i, V[i]);
    }

    while (M--) {
        int type; cin >> type;
        if (type == 1) {
            int a, b; cin >> a >> b;
            int old = V[a];
            V[a] = max(b, K);
            fenwick.add(a, V[a] - old);
        } else {
            int l, r, s; cin >> l >> r >> s;
            int tot = fenwick.query(l, r + 1);
            if (tot > s) {
                cout << "0\n";
            } else {
                int diff = s - tot;
                cout << fact[diff + r - l] * inv_fact[diff] % MOD * inv_fact[r - l] % MOD << '\n';
            }
        }
    }
}