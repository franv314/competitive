#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    for (;;) {
        bool ok = false;
        for (int i = 1; i < n - 1; i++) {
            if (s[i - 1] == '1' && s[i + 1] == '1' && s[i] != '1') {
                s[i] = '1';
                ok = true;
            }
        }
        if (!ok) break;
    }

    int ma = count(s.begin(), s.end(), '1');
    int mi = 0, cc = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            if (cc) mi += cc / 2 + 1;
            cc = 0;
        } else {
            cc++;
        }
    }
    if (cc) mi += cc / 2 + 1;

    cout << mi << " " << ma << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
