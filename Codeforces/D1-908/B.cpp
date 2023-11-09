#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    sort(b.rbegin(), b.rend());
    
    vector<int> highest_top(n + 1, INT_MIN);
    highest_top[0] = INT_MAX;

    map<int, vector<int>> ma;
    for (int i = n - 1; i >= 0; i--) {
        int l = 0, r = n + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;

            if (highest_top[m] > a[i]) l = m;
            else r = m;
        }
        int len = l + 1;

        ma[len].push_back(i);
        highest_top[len] = max(highest_top[len], a[i]);
    }

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && b[j] >= a[i]) {
            cout << b[j] << " ";
            j++;
        }
        cout << a[i] << " ";
    }

    while (j < m) {
        cout << b[j] << " ";
        j++;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}