#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> h(n);
    bool stop = false;
    for (auto &x: h) {
        cin >> x;
        if (x > n) stop = true;
    }
    if (stop) {
        cout << "NO\n";
        return;
    }

    reverse(h.begin(), h.end());
    vector<int> hhh;
    int first = 0;
    for (int hh = 1; hh <= n; hh++) {
        while (h[first] < hh) {
            first++;
        }
        hhh.push_back(n - first);
    }
    reverse(hhh.begin(), hhh.end());

    if (h == hhh) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}