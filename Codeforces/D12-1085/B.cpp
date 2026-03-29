#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, l; cin >> n >> m >> l;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> kill(l + 1), remkill;
    for (auto x: a) kill[x] = 1;

    remkill = kill;
    for (int i = l - 1; i >= 0; i--)
        remkill[i] += remkill[i + 1];

    auto check = [&](int k) {
        for (int M = 1; M <= m; M++) {
            multiset<int> val;
            for (int i = 0; i < M; i++)
                val.insert(0);
            for (int i = 1; i <= l; i++) {
                while (remkill[i] + 1 < val.size())
                    val.erase(val.begin());

                int mi = *val.begin();
                val.erase(val.begin());
                val.insert(mi + 1);

                if (kill[i]) {
                    int ma = *val.rbegin();
                    val.erase(val.find(ma));
                    val.insert(0);
                }
            }

            if (*max_element(val.begin(), val.end()) >= k) return true;
        }
        return false;
    };

    int low = 0, r = l + 1;
    while (r - low > 1) {
        int m = (low + r) / 2;
        // cerr << m << " " << check(m) << "\n";
        if (check(m)) low = m;
        else r = m;
    }
    cout << low << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
