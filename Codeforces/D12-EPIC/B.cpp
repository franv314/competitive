#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> b = a;
    for (int i = 1; i < n; i++)
        b[i] = max(b[i - 1], a[i]);

    vector<int> diffs(n);
    for (int i = 0; i < n; i++)
        diffs[i] = b[i] - a[i];

    sort(diffs.begin(), diffs.end());
    int last = 0;
    long long cost = 0;

    for (int i = 0; i < n; i++) {
        cost += (long long)(n - i + 1) * (diffs[i] - last);
        last = diffs[i];
    }

    cout << cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}