#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, b; cin >> n >> b;
    //assert(n == 100 && b >= 100);

    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        vector<char> q(n, '+');
        q[i] = '-';
        cout << '?';
        for (auto x: q) cout << ' ' << x;
        cout << endl;
        cin >> ans[i];
    }

    long long tot = accumulate(ans.begin(), ans.end(), 0ll) / (n - 2);
    cout << '!';
    for (int i = 0; i < n; i++) {
        cout << ' ' << (tot - ans[i]) / 2;
    }
    cout << endl;
}

int main() {
    int T; cin >> T;
    while (T--) solve();
}