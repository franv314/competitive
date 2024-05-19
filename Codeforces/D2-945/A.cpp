#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c; cin >> a >> b >> c;

    if ((a + b + c) & 1) return void(cout << "-1\n");
    if (c > a + b) return void(cout << a + b << '\n');

    int draw = 0;
    while (c) {
        c--;
        draw++;

        if (b > a) b--;
        else a--;
    }

    cout << draw + min(a, b) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}