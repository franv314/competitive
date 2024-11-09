#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> pref(n + 1);
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1];
        if (pref[i - 1] > a[i - 1]) pref[i]--;
        if (pref[i - 1] < a[i - 1]) pref[i]++;
    }

    auto check = [&](int m) -> bool {
        vector<int> suff(n + 1);
        suff[n] = m;
        int suff_min = 1e9;

        for (int i = n - 1; i >= 0; i--) {
            if (suff[i + 1] <= a[i])
                suff[i] = suff[i + 1] - 1;
            else
                suff[i] = suff[i + 1] + 1;
            
            suff_min = min(suff_min, suff[i + 1]);

            if (pref[i] >= suff_min)
                return true;
        }

        return false;
    };

    int l = 0, r = n + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m)) l = m;
        else r = m;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}