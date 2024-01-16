#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    multiset<int> grind;
    for (auto x: a) {
        auto it = grind.insert(x);
        if (next(it) != grind.end()) grind.erase(next(it));
    }

    cout << grind.size() << '\n';
}