#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, p; cin >> n >> p;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    long long tot_cost = p;
    map<int, long long> announcements;
    announcements[p] = n;
    for (int i = 0; i < n; i++) announcements[b[i]] += a[i];

    long long curr = 1;
    for (auto [cost, amount]: announcements) {
        if (curr + amount > n) {
            tot_cost += (n - curr) * (long long)cost;
            break;
        } else {
            curr += amount;
            tot_cost += amount * cost;
        }
    }
    cout << tot_cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}