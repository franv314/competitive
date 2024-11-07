#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;

    int cnt = 0;
    auto check = [&](int pos) {
        if (pos < 0 || pos >= s.size() - 3)
            return false;
        return s.substr(pos, 4) == "1100";
    };

    for (int i = 0; i < s.size() - 3; i++)
        cnt += check(i);

    int q; cin >> q;
    while (q--) {
        int i, v; cin >> i >> v;
        i--;

        cnt -= check(i - 3);
        cnt -= check(i - 2);
        cnt -= check(i - 1);
        cnt -= check(i - 0);

        s[i] = v + '0';

        cnt += check(i - 3);
        cnt += check(i - 2);
        cnt += check(i - 1);
        cnt += check(i - 0);

        cout << (cnt ? "YES\n" : "NO\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
