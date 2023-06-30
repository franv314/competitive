#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    s.push_back(' ');
    
    int ma = 0;
    int count = 0;
    char old = '<';
    for (auto c: s) {
        if (c != old) {
            ma = max(ma, count);
            count = 0;
            old = c;
        }
        count++;
    }
    cout << ma + 1 << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}