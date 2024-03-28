#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c; cin >> a >> b >> c;
    if (a < b && b < c) return void(cout << "STAIR\n");
    if (a < b && b > c) return void(cout << "PEAK\n");
    cout << "NONE\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}