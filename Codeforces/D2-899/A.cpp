#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int last = 0;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        if (a == last + 1) {
            last += 2;
        } else {
            last++;
        }
    }
    cout << last << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}