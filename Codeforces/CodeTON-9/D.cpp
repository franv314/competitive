#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (auto &x: a) cin >> x;
    reverse(a.begin(), a.end());

    vector<int> ans(n + 1, -1);

    for (int i = 0; i < m && count(ans.begin() + 1, ans.end(), -1); i++) {
        vector<bool> dont(n + 1);
        for (int j = 1; j <= n; j++) {
            if (ans[j] != -1 || dont[j]) continue;

            ans[j] = a[i];
            for (int k = j; k <= n; k += j)
                dont[k] = true;
        }
    }

    ans.erase(ans.begin());
    if (count(ans.begin(), ans.end(), -1))  
        return void(cout << "-1\n");

    for (auto x: ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
