#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x, y; cin >> n >> x >> y;
    vector<int> ans(n);

    for (int i = 1; i < y; i++)
        ans[i - 1] = (i % 2 == y % 2) ? +1 : -1;
    for (int i = x + 1; i <= n; i++)
        ans[i - 1] = (i % 2 == x % 2) ? +1 : -1;
    for (int i = y; i <= x; i++)
        ans[i - 1] = 1;

    for (auto x: ans)
        cout << x << ' ';
    cout << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}