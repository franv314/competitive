#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    cout << min(n, (int)count(s.begin(), s.end(), 'A'))
          + min(n, (int)count(s.begin(), s.end(), 'B'))
          + min(n, (int)count(s.begin(), s.end(), 'C'))
          + min(n, (int)count(s.begin(), s.end(), 'D')) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}