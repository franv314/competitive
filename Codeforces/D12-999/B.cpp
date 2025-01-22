#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, int, greater<int>> freq;
    for (auto x: a) freq[x]++;

    int p = -1;
    for (auto &[v, f]: freq) {
        if (f >= 4)
            return void(cout << v << " " << v << " " << v << " " << v << "\n");
        if (f < 2)
            continue;
        if (p != -1)
            return void(cout << v << " " << v << " " << p << " " << p << "\n");
        p = v;
        f -= 2;
    }

    for (auto it = freq.begin(); next(it) != freq.end(); it++) {
        if (it->second == 0)
            continue;
        while (next(it) != freq.end() && next(it)->second == 0)
            freq.erase(next(it));
        if (next(it) == freq.end())
            break;
        
        int v1 = it->first;
        int v2 = next(it)->first;

        if (v1 < v2 + 2 * p)
            return void(cout << p << " " << p << " " << v1 << " " << v2 << "\n");
    }

    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
