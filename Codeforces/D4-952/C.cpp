#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long sum = 0;
    set<long long> found;

    int cnt = 0;
    for (auto x: a) {
        found.insert(x);
        sum += x;
        cnt += (sum % 2 == 0) && found.count(sum / 2);
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}