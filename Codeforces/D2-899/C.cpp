#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> arr(n);
    long long sp = 0;

    for (auto &a: arr) {
        cin >> a;
        if (a >= 0) {
            sp += a;
        }
    }

    long long ma = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) sp -= arr[i];
        long long val = sp;
        if (i % 2 == 0) val += arr[i];
        ma = max(ma, val);
    }

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}