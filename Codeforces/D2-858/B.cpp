#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &x: a) cin >> x;

        int zeroes = count(a.begin(), a.end(), 0);
        if (zeroes <= (n + 1) / 2) {
            cout << 0 << "\n";
            continue;
        }

        if (zeroes == n || find_if(a.begin(), a.end(), [](int x){ return x > 1; }) != a.end()) {
            cout << 1 << "\n";
        } else {
            cout << 2 << "\n";
        }
    }
}