#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long x; cin >> x;
    vector<int> ans;
    int small = -1000, big = 0;

    vector<int> digits;
    for (long long i = x; i; i /= 2) {
        digits.push_back(i % 2);
    }
    digits.pop_back();
    reverse(digits.begin(), digits.end());

    for (auto x: digits) {
        ans.push_back(big);
        big++;

        if (x) {
            ans.push_back(small);
            small--;
        }
    }

    cout << ans.size() << '\n';
    for (auto x: ans) cout << x << ' '; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}