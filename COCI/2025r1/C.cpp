#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> deg(n), degfreq(n);
    vector<set<int>> sup(n);
    degfreq[0] = n;

    auto incr = [&](int u) {
        degfreq[deg[u]]--;
        deg[u]++;
        degfreq[deg[u]]++;
    };
    auto decr = [&](int u) {
        degfreq[deg[u]]--;
        deg[u]--;
        degfreq[deg[u]]++;
    };
    auto check = [&] {
        return degfreq[0] == 1 && degfreq[1] == n - 1;
    };

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        incr(v);
        sup[v].insert(u);
    }

    cout << (check() ? "DA\n" : "NE\n");

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;

        if (sup[a].count(b)) {
            decr(a);
            incr(b);
            sup[a].erase(b);
            sup[b].insert(a);
        } else {
            incr(a);
            decr(b);
            sup[b].erase(a);
            sup[a].insert(b);
        }

        cout << (check() ? "DA\n" : "NE\n");
    }
}