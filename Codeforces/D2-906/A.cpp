#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    map<int, int> vals;

    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        vals[v]++;
    }

    if (vals.size() == 1) {
        cout << "Yes\n";
    } else if (vals.size() > 2) {
        cout << "No\n";
    } else if (abs(vals.rbegin()->second - vals.begin()->second) <= 1) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}