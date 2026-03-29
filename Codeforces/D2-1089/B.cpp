#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordtree = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto &x: p) { cin >> x; x--; }

    ordtree<int> pref;
    int base = 0, ma = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] <= i) {
            base++;
        } else {
            pref.insert(p[i]);
        }

        int ans = base + pref.order_of_key(i);
        ma = max(ma, ans);
    }

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
