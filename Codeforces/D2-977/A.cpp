#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    multiset<int> a;
    while (n--) {
        int x; cin >> x;
        a.insert(x);
    }

    while (a.size() > 1) {
        int o1 = *a.begin(); a.erase(a.begin());
        int o2 = *a.begin(); a.erase(a.begin());
        a.insert((o1 + o2) / 2);
    }

    cout << *a.begin() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}