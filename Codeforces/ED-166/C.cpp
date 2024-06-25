#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n + m + 1), b(n + m + 1);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    vector<long long> pa(n + m + 2), pb(n + m + 2), pbest(n + m + 2);
    vector<int> pp(n + m + 2), pt(n + m + 2);

    for (int i = 0; i <= n + m; i++) {
        pa[i + 1] = pa[i] + a[i];
        pb[i + 1] = pb[i] + b[i];
        pbest[i + 1] = pbest[i] + max(a[i], b[i]);
        pp[i + 1] = pp[i] + (a[i] > b[i]);
        pt[i + 1] = pt[i] + (a[i] < b[i]);
    }

    auto binsearch = [&](int excluded) -> pair<bool, int> {
        int l = -1, r = n + m + 1;
        bool stop;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            
            int cntp = pp[mid + 1] - (a[excluded] > b[excluded] && excluded <= mid);
            int cntt = pt[mid + 1] - (a[excluded] < b[excluded] && excluded <= mid);

            if (cntp > n) {
                r = mid;
                stop = false;
            } else if (cntt > m) {
                r = mid;
                stop = true;
            } else {
                l = mid;
            }
        }
        return {stop, r};
    };

    for (int i = 0; i <= n + m; i++) {
        auto [type, pos] = binsearch(i);
        long long score = pbest[pos];
        if (type) {
            score += pa.back() - pa[pos];
            if (i < pos) {
                score -= max(a[i], b[i]);
            } else {
                score -= a[i];
            }
        } else {
            score += pb.back() - pb[pos];
            if (i < pos) {
                score -= max(a[i], b[i]);
            } else {
                score -= b[i];
            }
        }

        cout << score << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}