#include <bits/stdc++.h>
using namespace std;

#define MAXV 1'000'000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<int>> primes(MAXV + 1);
    for (int i = 2; i <= MAXV; i++) {
        if (!primes[i].empty()) continue;
        for (int j = i; j <= MAXV; j += i) {
            primes[j].push_back(i);
        }
    }

    vector<vector<pair<int, int>>> checks(MAXV + 1);
    for (int i = 1; i <= MAXV; i++) {
        for (int mask = 1; mask < (1 << primes[i].size()); mask++) {
            int val = 1;
            for (int j = 0; j < primes[i].size(); j++) {
                if ((mask >> j) & 1) {
                    val *= primes[i][j];
                }
            }
            checks[i].emplace_back(val, __builtin_popcount(mask) & 1 ?: -1);
        }
    }

    vector<int> cnt(MAXV + 1);
    for (auto x: a) {
        for (auto [v, _]: checks[x]) {
            cnt[v]++;
        }
    }

    long long ans = (long long)n * n;
    for (auto x: a) {
        for (auto [v, c]: checks[x]) {
            ans -= cnt[v] * c;
        }
    }

    cout << (ans - count(a.begin(), a.end(), 1)) / 2 << '\n';
}