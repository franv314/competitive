#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> vals;
    while (n--) {
        int v; cin >> v;
        vals.insert(v);
    }   
    cout << 2 * vals.size() - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
