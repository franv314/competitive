#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> vals;
    for (auto &x: a) {
        cin >> x;
        vals[x]++;
    }
    map<int, int> diff;
    
    for (auto it = next(vals.begin()); it != vals.end(); it++) {
        diff[it->first - prev(it)->first]++;
    }

    int q; cin >> q;
    while (q--) {
        int p, x; cin >> p >> x;
        p--;

        if (--vals[a[p]] == 0) {
            auto it = vals.find(a[p]);
            if (it != vals.begin()) {
                int pv = prev(it)->first;
                if (--diff[a[p] - pv] == 0) {
                    diff.erase(a[p] - pv);
                }
            }
            if (it != prev(vals.end())) {
                int nx = next(it)->first;
                if (--diff[nx - a[p]] == 0) {
                    diff.erase(nx - a[p]);
                }
            }

            if (it != vals.begin() && it != prev(vals.end())) {
                int pv = prev(it)->first;
                int nx = next(it)->first;
                diff[nx - pv]++;
            }

            vals.erase(a[p]);
        }

        a[p] = x;
        if (vals[a[p]]++ == 0) {
            auto it = vals.find(a[p]);
            if (it != vals.begin()) {
                int pv = prev(it)->first;
                diff[a[p] - pv]++;
            }
            if (it != prev(vals.end())) {
                int nx = next(it)->first;
                diff[nx - a[p]]++;
            }

            if (it != vals.begin() && it != prev(vals.end())) {
                int pv = prev(it)->first;
                int nx = next(it)->first;
                if (--diff[nx - pv] == 0) {
                    diff.erase(nx - pv);
                }
            }
        }

        cout << vals.rbegin()->first + (diff.empty() ? 0 : diff.rbegin()->first) << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}