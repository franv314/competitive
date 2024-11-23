#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    for (int i = 0; i <= (int)s.size() - 3; i++)
        if (s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2])
            return void(cout << s.substr(i, 3) << '\n');
    for (int i = 0; i <= (int)s.size() - 2; i++)
        if (s[i] == s[i + 1])
            return void(cout << s.substr(i, 2) << '\n');
    
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
