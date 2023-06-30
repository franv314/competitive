#include <bits/stdc++.h>
using namespace std;



void solve() {
    int A, B, C;
    cin >> A >> B >> C;

    assert(C == 0);

    if ((A + B) % 2) {
        if (A == B + 1 || B == A + 1) cout << 1 << '\n';
        else cout << 0 << '\n';
        return;
    }
    if (A == B) cout << 2 << '\n';
    else cout << 0 << '\n';
}

int main() {
    int T; cin >> T;
    while (T--) solve();
}