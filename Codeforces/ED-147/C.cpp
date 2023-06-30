#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;

    int best = INT_MAX;

    for (char l = 'a'; l <= 'z'; l++) {
        int ma = 0;
        int curr_block = 0;
        for (auto c: s) {
            if (c != l) curr_block++;
            else curr_block = 0;
            ma = max(ma, curr_block);
        }

        if (ma == 0) {
            best = 0;
            break;
        }
        best = min(best, 1 + (int)log2(ma));
    }
    cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}