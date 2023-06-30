#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    bool found = false;

    int ans = 1;

    for (auto c: s) {
        if (c == '0' && !found) {
            ans *= 0;
        } else if (c == '?') {
            if (found) {
                ans *= 10;
            } else {
                ans *= 9;
            }
            found = true;
        } else {
            found = true;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}