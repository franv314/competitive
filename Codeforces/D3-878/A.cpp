#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    string a;
    
    int i = 0;
    while (i < n) {
        char c = s[i];
        a.push_back(c);
        while (s[++i] != c) ;
        i++;
    }
    cout << a << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}