#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
 
    sort(a.begin(), a.end());
    vector<int> d(n - 1);
    for (int i = 1; i < n; i++)
        d[i - 1] = a[i] - a[i - 1];
    
    vector<i64> ps_odd(n), ps_even(n);
    for (int i = 0; i < n - 1; i++) {
        ps_odd[i + 1] = ps_odd[i];
        ps_even[i + 1] = ps_even[i];
        if (i % 2)
            ps_odd[i + 1] += d[i];
        else
            ps_even[i + 1] += d[i];
    }

    auto eval = [&](int l, int r) {
        if (r < l) return 0LL;
        if (l % 2) return ps_odd[r + 1] - ps_odd[l];
        return ps_even[r + 1] - ps_even[l];
    };

    set<pair<int, int>> ccs;
    set<tuple<int, int, int>> best_cc;

    for (int i = 0; i < n - 1; i++) {
        ccs.emplace(i + 1, i - 1);
        best_cc.emplace(eval(i, i), i + 1, i - 1);
    }

    int ans = 0;
    for (int i = 0; i < n / 2; i++) {

        auto [v, l, r] = *best_cc.begin(); best_cc.erase(best_cc.begin());

        auto it = ccs.find({l, r});
        l--, r++;
        
        if (next(it) != ccs.end()) {
            auto [nl, nr] = *next(it);
            best_cc.erase({eval(nl - 1, nr + 1) - eval(nl, nr), nl, nr});
            ccs.erase(next(it));
            r = nr;
        }
        if (it != ccs.begin()) {
            auto [nl, nr] = *prev(it);
            best_cc.erase({eval(nl - 1, nr + 1) - eval(nl, nr), nl, nr});
            ccs.erase(prev(it));
            l = nl;
        }

        ccs.erase(it);
        ccs.emplace(l, r);
        if (l != 0 && r != n - 2) {
            best_cc.emplace(eval(l - 1, r + 1) - eval(l, r), l, r);
        }

        cout << (ans += v) << ' ';
    }
}
