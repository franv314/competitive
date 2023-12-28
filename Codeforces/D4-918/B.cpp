#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    for (int i = 0; i < 3; i++) {
        cin >> s;
        if (s.find('?') != string::npos) {
            if (s.find('A') == string::npos) {
                cout << "A\n";
            }
            if (s.find('B') == string::npos) {
                cout << "B\n";
            }
            if (s.find('C') == string::npos) {
                cout << "C\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}