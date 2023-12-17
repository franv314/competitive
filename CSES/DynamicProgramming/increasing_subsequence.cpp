#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    set<int> lis;
    for (auto x: a) {
        auto [it, ok] = lis.insert(x);
        if (ok && next(it) != lis.end()) lis.erase(next(it));
    }

    cout << lis.size() << '\n';
}