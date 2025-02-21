#include <bits/stdc++.h>
using namespace std;

struct SegTree {

};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    bool found = false;
    vector<int> b;

    for (auto x: a) {
        if (x) b.push_back(x);
        else if (!found) {
            b.push_back(0);
            found = true;
        }
    } 

    set<int> mex;
    for (int i = 0; i <= n; i++)
        mex.insert(i);
    reverse(b.begin(), b.end());

    bool ok = true;
    for (auto x: b) {
        if (x < *mex.begin()) {
            ok = false;
            break;
        }
        mex.erase(x);
    }

    cout << b.size() - !ok << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
