#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c; cin >> a >> b >> c;

    multiset<int> pos;
    pos.insert(0);

    int ma = -1;

    while (a--) {
        if (pos.empty()) return void(cout << "-1\n");
        int h = *pos.begin(); pos.erase(pos.begin());
        ma = max(ma, h);
        pos.insert(h + 1);
        pos.insert(h + 1);
    }

    while (b--) {
        if (pos.empty()) return void(cout << "-1\n");
        int h = *pos.begin(); pos.erase(pos.begin());
        ma = max(ma, h);
        pos.insert(h + 1);
    }

    while (c--) {
        if (pos.empty()) return void(cout << "-1\n");
        int h = *pos.begin(); pos.erase(pos.begin());
        ma = max(ma, h);
    }

    if (!pos.empty()) return void(cout << "-1\n");

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}