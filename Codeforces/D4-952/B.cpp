#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    pair<int, int> ma = {-1, -1};
    for (int i = 2; i <= n; i++) {
        int s = 0;
        for (int j = i; j <= n; j += i)
            s += j;
        ma = max(ma, {s, i});
    }
    cout << ma.second << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}