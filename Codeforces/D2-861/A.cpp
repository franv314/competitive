#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int l, r; cin >> l >> r;
        pair<int, int> best = {INT_MIN, 0};
        for (int i = l; i <= min(r, l + 200); i++) {
            int ma = INT_MIN, mi = INT_MAX;
            for (int j = i; j; j /= 10) {
                ma = max(ma, j % 10);
                mi = min(mi, j % 10);
            }
            best = max(best, {ma - mi, i});
        }
        cout << best.second << "\n";
    }
}