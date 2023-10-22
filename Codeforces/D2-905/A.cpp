#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> freq(26);
    for (auto c: s) {
        freq[c - 'a']++;
    }

    int cnt = 0;
    for (auto x: freq) {
        if (x & 1) {
            cnt++;
        }
    }

    if (cnt - 1 <= k) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}