#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++)
        cin >> l[i] >> r[i];

    set<int> free;
    for (int i = 1; i <= 2 * n; i++)
        free.insert(i);
    
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        if (l[i] == r[i]) {
            cnt[l[i]]++;
            free.erase(l[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (l[i] == r[i]) {
            if (--cnt[l[i]] == 0)
                free.insert(l[i]);
        }

        auto it = free.lower_bound(l[i]);
        if (it == free.end() || *it > r[i])
            cout << 0;
        else
            cout << 1;

        if (l[i] == r[i]) {
            ++cnt[l[i]];
            free.erase(l[i]);
        }
    }

    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
