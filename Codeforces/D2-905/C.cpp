#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);

    for (auto &x: a) cin >> x;

    vector<int> starts, ends;
    set<int> found;
    for (int i = 0; i < n; i++) {
        if (!found.count(a[i])) starts.push_back(i);
        found.insert(a[i]);
    } 

    found.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (!found.count(a[i])) ends.push_back(i + 1);
        found.insert(a[i]);
    }

    long long total = 0;
    for (auto s: starts) {
        while (ends.back() <= s) ends.pop_back();
        total += ends.size();
    }

    cout << total << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}