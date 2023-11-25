#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    int l = 0, r = n - 1;
    while (l < s.size() && s[l] == 'B') l++;
    while (r > 0 && s[r] == 'A') r--;

    cout << max(r - l, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}