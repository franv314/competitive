#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    set<int> ex;
    for (int i = 0; i <= n; i++) ex.insert(i);

    for (auto x: a) {
        int hit = *next(ex.begin()) - *ex.begin();
        if (x == hit) {
            cout << *ex.begin() << ' ';
            ex.erase(ex.begin());
        } else {
            cout << *ex.begin() - x << ' ';
            ex.erase(*ex.begin() - x); 
        }
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}