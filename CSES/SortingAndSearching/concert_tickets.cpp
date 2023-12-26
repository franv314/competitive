#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    multiset<int, greater<int>> h;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        h.insert(v);
    }

    while (m--) {
        int v; cin >> v;
        auto it = h.lower_bound(v);

        if (it == h.end()) cout << "-1\n";
        else {
            cout << *it << '\n';
            h.erase(it);
        }
    }
}