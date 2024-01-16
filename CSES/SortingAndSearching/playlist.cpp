#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> k(n);
    for (auto &x: k) cin >> x;

    set<int> curr;
    int r = 0;

    int ans = 0;

    for (int l = 0; l < n; l++) {
        while (r < n && !curr.count(k[r])) {
            curr.insert(k[r++]);
        }

        ans = max(ans, (int)curr.size());
        curr.erase(k[l]);
    }

    cout << ans << '\n';
}