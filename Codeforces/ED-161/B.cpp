#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    map<int, long long> am;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        am[a]++;
    }

    int shorter = 0;
    long long ans = 0;
    for (auto [_, x]: am) {
        ans += shorter * x * (x - 1) / 2;
        ans += x * (x - 1) * (x - 2) / 6;
        shorter += x;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}