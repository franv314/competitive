#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a, b, c;
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        a.push_back(y);
    }
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        b.push_back(y);
    }
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        c.push_back(y);
    }
    
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    reverse(c.begin(), c.end());
    
    int curr = 0;
    for (;;) {
        bool made_move = false;
        if (!a.empty() && (a.back() & ~x) == 0) {
            made_move = true;
            curr |= a.back();
            a.pop_back();
        }
        if (!b.empty() && (b.back() & ~x) == 0) {
            made_move = true;
            curr |= b.back();
            b.pop_back();
        }
        if (!c.empty() && (c.back() & ~x) == 0) {
            made_move = true;
            curr |= c.back();
            c.pop_back();
        }
        if (!made_move) break;
    }
    if (curr == x) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}