#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    int n; cin >> n;
    vector<i64> a(n);
    for (auto &x: a) cin >> x;

    auto rec = [&](auto &&rec, vector<i64> vec) -> i64 {
        if (vec.size() == 1) {
            return vec[0];
        }

        i64 ans = accumulate(vec.begin(), vec.end(), 0LL);
        vector<i64> dir(vec.size() - 1), rev(vec.size() - 1);

        for (int i = 0; i < vec.size() - 1; i++) {
            dir[i] = vec[i + 1] - vec[i];
            rev[i] = vec[vec.size() - i - 2] - vec[vec.size() - i - 1];
        }

        if (vec.size() != n) ans = abs(ans);
        return max(ans, abs(rec(rec, dir)));
    };

    cout << rec(rec, a) << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
