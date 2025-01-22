#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    multiset<int> num(a.begin(), a.end());
    int pairs = 0;
    while (!num.empty()) {
        int v = *num.begin(); num.erase(num.begin());
        auto it = num.lower_bound(k - v);
        if (it == num.end() || *it != k - v)
            continue;

        pairs++;
        num.erase(it);
    }

    cout << pairs << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
