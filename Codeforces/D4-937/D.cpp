#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000
bool dp[MAXN + 1];

void precalc() {
    vector<int> att;
    for (int i = 1; i < 32; i++) att.push_back(stoi(format("{:b}", i)));

    dp[1] = true;
    for (int i = 2; i <= MAXN; i++) {
        for (auto j: att) {
            dp[i] |= (i % j == 0) && dp[i / j];
        }
    }
}

void solve() {
    int n; cin >> n;
    cout << (dp[n] ? "YES\n" : "NO\n");
}

int main() {
    precalc();

    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}