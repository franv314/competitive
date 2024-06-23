#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    if (n == 2) {
        if (s[0] != '0') cout << s << '\n';
        else cout << s[1] << '\n';
        return;
    }

    int mi = 1e9;

    for (int skip = 0; skip < n - 1; skip++) {
        int curr = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            curr = 10 * curr + s[i] - '0';
            if (i == skip) continue;
            if (curr == 0) return void(cout << "0\n");
            if (curr != 1) res += curr;
            curr = 0;
        }
        if (res == 0) res = 1;
        mi = min(mi, res);
    }

    cout << mi << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}