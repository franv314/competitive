#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;

    char last = '0';
    for (auto &c: s) {
        if (c == '?') c = last;
        last = c;
    } 
    cout << s << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}