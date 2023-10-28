#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;

    bool s_good = true, t_good = true;

    for (int i = 0; i < n - 1; i++) {
        s_good &= s[i] != s[i + 1];
    }
    for (int i = 0; i < m - 1; i++) {
        t_good &= t[i] != t[i + 1];
    }

    if (s_good) {
        cout << "Yes\n";
    } else if (!t_good) {
        cout << "No\n";
    } else {
        if (t.front() != t.back()) {
            cout << "No\n";
        } else if (t.front() == '0') {
            bool ok = true;
            for (int i = 0; i < n - 1; i++) {
                ok &= s[i] != '0' || s[i + 1] != '0';
            }

            if (ok) {
                cout << "Yes\n";
            } else{
                cout << "No\n";
            }
        } else {
            bool ok = true;
            for (int i = 0; i < n - 1; i++) {
                ok &= s[i] != '1' || s[i + 1] != '1';
            }

            if (ok) {
                cout << "Yes\n";
            } else{
                cout << "No\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}