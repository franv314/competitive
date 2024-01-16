#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x, n; cin >> x >> n;

    set<int> pos;
    multiset<int> diff;
    pos.emplace(0);
    pos.emplace(x);
    diff.emplace(x);

    while (n--) {
        int p; cin >> p;
        auto [it, ok] = pos.insert(p);

        diff.erase(diff.find(*next(it) - *prev(it)));
        diff.insert(*next(it) - p);
        diff.insert(p - *prev(it));
    
        cout << *diff.rbegin() << ' ';
    }
    cout << '\n';
}