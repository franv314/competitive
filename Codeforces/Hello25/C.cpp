#include <bits/stdc++.h>
using namespace std;

using uint = unsigned;

void solve() {
    uint l, r; cin >> l >> r;

    uint i = 30, mask = UINT32_MAX;
    
    auto check = [&]() {
        return (l & (mask << i)) != (r & (mask << i));
    };

    while (!check()) {
        i--;
    }

    mask <<= i;
    int val1 = r & mask;

    cout << val1 << " ";
    if (r == val1) {
        cout << val1 - 1 << " " << val1 - 2 << "\n";
    } else {
        cout << val1 - 1 << " " << val1 + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
