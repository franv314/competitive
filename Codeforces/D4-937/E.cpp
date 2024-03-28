#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i) continue;
        divs.push_back(i);
        divs.push_back(n / i);
    }

    sort(divs.begin(), divs.end());

    for (auto d: divs) {
        string att1 = s.substr(0, d);
        string att2 = s.substr(n - d, d);

        int err1 = 0, err2 = 0;
        for (int i = 0; i < n; i++) {
            err1 += s[i] != att1[i % d];
            err2 += s[i] != att2[i % d];
        }

        if (err1 < 2 || err2 < 2) return void(cout << d << '\n');
    }

    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}