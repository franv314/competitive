#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, t; cin >> n >> t;

    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long l = 0, r = 1e18 + 10;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
    
        long long tot = 0;
        for (auto x: a) {
            tot += m / x;
            if (tot >= t) break;
        }

        if (tot >= t) r = m;
        else l = m;
    }

    cout << r << '\n';
}