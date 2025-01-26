#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    cout << count(s.begin(), s.end(), '1') << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
