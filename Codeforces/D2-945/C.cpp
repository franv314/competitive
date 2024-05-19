#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto &x: p) cin >> x;

    bool odd_1 = (find(p.begin(), p.end(), 1) - p.begin()) & 1;

    vector<int> q(n);
    vector<int> pri(n);
    iota(pri.begin(), pri.end(), 0);

    if (odd_1) {
        sort(pri.begin(), pri.end(), [&](int i, int j) {
            return make_pair(i % 2, p[i]) > make_pair(j % 2, p[j]);
        });
    } else {
        sort(pri.begin(), pri.end(), [&](int i, int j) {
            return make_pair(i % 2, -p[i]) < make_pair(j % 2, -p[j]);
        });
    }

    for (int i = 0; i < n; i++) {
        q[pri[i]] = i + 1;
    }

    for (auto x: q) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}