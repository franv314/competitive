#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    int curr = s[0] - '0';
    int dir = +1;

    int mi = curr, ma = curr;

    for (int i = 1; i < n; i++) {
        if (s[i] - '0' == abs(curr) % 2) {
            dir *= -1;
        } else {
            curr += dir;
        }

        mi = min(mi, curr);
        ma = max(ma, curr);
    }

    cout << ma - mi + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}