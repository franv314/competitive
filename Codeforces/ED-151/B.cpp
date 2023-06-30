#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long xa, ya; cin >> xa >> ya;
    long long xb, yb; cin >> xb >> yb;
    long long xc, yc; cin >> xc >> yc;
    
    xb -= xa, xc -= xa, yb -= ya, yc -= ya;
    
    if (xb * xc <= 0 && yb * yc <= 0) {
        cout << "1\n";
        return;
    }
    if (xb * xc <= 0) {
        cout << 1 + min(abs(yb), abs(yc)) << '\n';
        return;
    }
    if (yb * yc <= 0) {
        cout << 1 + min(abs(xb), abs(xc)) << '\n';
        return;
    }
    cout << 1 + min(abs(xb), abs(xc)) + min(abs(yb), abs(yc)) << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}