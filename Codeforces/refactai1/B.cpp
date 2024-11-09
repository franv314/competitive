#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s, t; cin >> s >> t;

    int zeros = count(s.begin(), s.end(), '0');
    int ones = count(s.begin(), s.end(), '1');

    for (auto c: t) {
        if (zeros == 0 || ones == 0) return void(cout << "NO\n");

        if (c == '0')
            ones--;
        else
            zeros--;
    }

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}