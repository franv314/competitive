#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int ans = 0;
    int curr = 0;

    for (auto x: a) {
        while (curr != m && b[curr] < x - k) curr++;
        if (curr == m) break;

        if (b[curr] > x + k) continue;
        ans++;
        curr++;
    }

    cout << ans << '\n';
}