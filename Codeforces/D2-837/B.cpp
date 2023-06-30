#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

typedef long long LL;

int lower_bound(set<int> s, int v) {
    if (s.lower_bound(v) == s.end()) return 1e9;
    return *s.lower_bound(v);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        map<int, set<int>> no_friends;
        while (m--) {
            int x, y; cin >> x >> y;
            no_friends[x - 1].insert(y - 1);
            no_friends[y - 1].insert(x - 1);
        }
        LL total = 0;
        int r = 0;
        for (int l = 0; l < n; l++) {
            while (r < n && lower_bound(no_friends[r], l) > r)
                r++;
            total += r - l;
        }
        cout << total << endl;
    }
}