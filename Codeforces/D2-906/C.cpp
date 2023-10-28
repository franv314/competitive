#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    if (n % 2) return void(cout << "-1\n");

    vector<int> moves;
    int i;
    for (i = 0; i < s.size() / 2 && i < 300; i++) {
        if (s[i] == s[s.size() - i - 1]) {
            if (s[i] == '0') {
                moves.push_back(s.size() - i);
                s.insert(s.end() - i, '0');
                s.insert(s.end() - i, '1');
            } else {
                moves.push_back(i);
                s.insert(s.begin() + i, '0');
                s.insert(s.begin() + i + 1, '1');
            }
        }
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == s[s.size() - 1 - i]) return void(cout << "-1\n");
    }

    cout << moves.size() << '\n';
    for (auto x: moves) cout << x << ' '; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}