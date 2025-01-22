#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    long long sa = accumulate(a.begin(), a.end(), 0LL);
    long long sb = accumulate(b.begin(), b.end(), 0LL);

    if (sa != sb)
        return void(cout << "No\n");

    multiset<int> as(a.begin(), a.end());
    multiset<int> bs(b.begin(), b.end());

    while (!bs.empty()) {
        int x = *bs.begin(); bs.erase(bs.begin());
        auto it = as.find(x);
        if (it != as.end()) {
            as.erase(it);
        } else if (bs.size() + 2 > as.size()) {
            return void(cout << "No\n");
        } else {
            bs.insert(x / 2);
            bs.insert((x + 1) / 2);
        }
    }

    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
