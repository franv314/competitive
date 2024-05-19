#include <bits/stdc++.h>
using namespace std;

#define MAXA 200'000

void solve() {
    int N, L; cin >> N >> L;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    long long sum = 0;
    vector<long long> suff;

    for (int i = L - 1; i >= 0; i -= 2) {
        sum += i;
        suff.push_back(sum);
    }

    vector<int> dp(MAXA + 1, 1e9);
    dp[0] = 0;

    for (auto x: suff) {
        for (long long i = x; i <= MAXA; i++) {
            dp[i] = min(dp[i], 1 + dp[i - x]);
        }
    }

    for (auto &x: A) {
        if (dp[x] == 1e9) {
            cout << -1 << '\n';
        } else {
            cout << dp[x] << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}