#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    sort(a.begin(), a.end());

    multiset<int> even, odd;
    for (auto x: a) {
        if (x & 1) {
            odd.insert(x);
        } else {
            even.insert(x);
        }
    }

    if (even.empty() || odd.empty()) {
        return void(cout << "0\n");
    }

    int wc = even.size() + 1;

    while (!even.empty()) {
        int x = *even.begin(); even.erase(even.begin());
        auto it = prev(odd.end());
        if (*it < x) {
            return void(cout << wc << '\n');
        }
        odd.insert(x + *it);
    }

    cout << wc - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}