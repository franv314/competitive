#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    long long m = accumulate(a.begin(), a.end(), 0LL) / 2;

    int cut;
    long long acc = 0;
    for (cut = 0; cut < n; cut++) {
        if (acc + a[cut] > m) {
            break;
        }
        acc += a[cut];
    }

    vector<array<long long, 3>> groups = {{acc, 0, cut}, {a[cut], cut, cut + 1}, {2 * m - a[cut] - acc, cut + 1, n}};
    sort(groups.rbegin(), groups.rend());

    vector<array<long long, 4>> ass = {
        {k, 0, 0, groups[0][0] - k},
        {0, groups[1][0] - m + k, m - k, 0},
        {0, m - groups[1][0], 0, m - groups[0][0]}
    };

    vector<array<long long, 4>> ans(n);
    
    auto assign = [&](int l, int r, array<long long, 4> target) {
        int idx = 0;
        for (int i = l; i < r; i++) {
            while (a[i]) {
                while (idx < 4 && target[idx] == 0) idx++;
                if (idx == 4) return;
                ans[i][idx] = min(target[idx], (long long)a[i]);
                target[idx] -= ans[i][idx];
                a[i] -= ans[i][idx];
            }
        }
    };

    for (int i = 0; i < 3; i++) {
        auto [_, l, r] = groups[i];
        assign(l, r, ass[i]);
    }

    for (auto [w, x, y, z]: ans) {
        cout << w << " " << x << " " << y << " " << z << '\n';
    }
}