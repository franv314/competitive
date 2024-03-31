#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    map<int, int> freq;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        freq[x]++;
    }

    bool bonus = true;
    for (int i = 0; ; i++) {
        if (freq[i] == 0) return void(cout << i << '\n');
        if (freq[i] == 1 && bonus) bonus = false;
        else if (freq[i] == 1) return void(cout << i << '\n');
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
