#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    set<int> legal;
    for (int i = 0; i <= n; i++)
        legal.insert(i);
    deque<int> ans;
    for (int i = n - 1; i >= 0; i--) {
        legal.erase(a[i]);
        if (i != n - 1 && a[i] == a[i + 1])
            legal.erase(ans.front());
        ans.push_front(*legal.begin());
    }

    Tree<int> mex;
    for (int i = 0; i <= n; i++)
        mex.insert(i);
    
    bool ok = true;
    for (int i = 0; i < n; i++) {
        mex.erase(ans[i]);
        ok &= a[i] == *mex.find_by_order(n - 1 - i);
    }

    if (!ok) return void(cout << "NO\n");
    cout << "YES\n";
    for (auto x: ans) cout << x << ' '; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
