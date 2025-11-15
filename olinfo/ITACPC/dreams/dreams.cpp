#include <bits/stdc++.h>
using namespace std;

constexpr int MAXB = 1e7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> ps(MAXB + 1);
    for (int i = 1; i <= MAXB; i++) {
        string s = to_string(i);
        string t(s.rbegin(), s.rend());
        ps[i] = ps[i - 1] + (s == t);
    }

    int t; cin >> t;
    while (t--) {
        int l, r; cin >> l >> r;
        cout << ps[r] - ps[l - 1] << '\n';
    }
}