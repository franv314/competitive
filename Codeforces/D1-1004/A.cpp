#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> x(n);
    for (auto &v: x) cin >> v;

    set<int> vals;
    for (int i = 1; i <= n; i++)
        vals.insert(i);
    
    for (auto v: x)
        vals.erase(v);

    if (!vals.empty()) {
        int i = *vals.begin();
        int j = i % n + 1;

        cout << "? " << i << " " << j << endl;
        int ans; cin >> ans;

        if (ans == 0)
            cout << "! A" << endl;
        else
            cout << "! B" << endl;
    } else {
        int p1 = find(x.begin(), x.end(), 1) - x.begin() + 1;
        int pn = find(x.begin(), x.end(), n) - x.begin() + 1;

        cout << "? " << p1 << " " << pn << endl;
        int ans1; cin >> ans1;

        cout << "? " << pn << " " << p1 << endl;
        int ans2; cin >> ans2;

        if (ans1 < n - 1 || ans2 < n - 1)
            cout << "! A" << endl;
        else
            cout << "! B" << endl;
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
