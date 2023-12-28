#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> p(n);

    for (auto &[a, b]: p) cin >> a >> b;

    sort(p.begin(), p.end());
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> st;

    for (auto [a, b]: p) {
        st.insert(b);
    }

    long long ans = 0;
    for (auto [a, b]: p) {
        st.erase(b);
        int v = st.order_of_key(b);
        ans += v;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}