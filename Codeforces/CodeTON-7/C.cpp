#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n), b(n);
    for (auto &e: a) cin >> e;
    for (auto &e: b) cin >> e;

    vector<int> orig = a;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int y = n - x;

    multimap<int, int> ans;

    for (int i = 0; i < x; i++) {
        if (a[n - 1 - i] <= b[x - 1 - i]) {
            return void(cout << "NO\n");
        }
        ans.emplace(a[n - 1 - i], b[x - 1 - i]);
    }

    for (int i = 0; i < y; i++) {
        if (a[i] > b[i + x]) {
            return void(cout << "NO\n");
        }
        ans.emplace(a[i], b[i + x]);
    }

    cout << "YES\n";

    for (auto x: orig) {
        auto it = ans.find(x);
        cout << it->second << ' ';
        ans.erase(it);
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}