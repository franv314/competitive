#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> H(N);
    for (auto &x: H) cin >> x;

    vector<pair<i64, i64>> lines;
    for (int i = 0; i < N - 1; i++) {
        i64 m = H[i + 1] - H[i];
        i64 q = H[i] - m * i;
        lines.emplace_back(m, q);
    }

    sort(lines.begin(), lines.end());
    vector<i64> ans(N);

    auto rec = [&](auto &&rec, int l1, int r1, int l2, int r2) {
        if (l1 == r1) return;
        int m1 = (l1 + r1) / 2;
        
        pair<i64, int> ma = {-1, -1};
        for (int i = l2; i < r2; i++) {
            ma = max(ma, {lines[i].first * m1 + lines[i].second, i});
        }

        ans[m1] = ma.first;
        rec(rec, l1, m1, l2, ma.second + 1);
        rec(rec, m1 + 1, r1, ma.second, r2);
    };

    rec(rec, 0, N, 0, N - 1);

    for (int i = 0; i < N; i++) {
        cout << max(ans[i] - H[i], 0LL) << ' ';
    }
    cout << '\n';
}