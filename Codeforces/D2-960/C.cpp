#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long sum = 0;

    auto step = [&]() {
        sum += accumulate(a.begin(), a.end(), 0LL);

        map<int, int> freq;
        int mad = 0;

        for (int i = 0; i < n; i++) {
            if (++freq[a[i]] >= 2)
                mad = max(mad, a[i]);
            a[i] = mad;
        }
    };

    step();
    step();

    long long ps = 0;
    for (auto x: a) {
        ps += x;
        sum += ps;
    }
    
    cout << sum << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}