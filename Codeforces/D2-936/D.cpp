#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> pxor(n + 1);
    for (int i = 0; i < n; i++) pxor[i + 1] = pxor[i] ^ a[i];

    auto check = [&](int allow) {
        if ((pxor[n] | allow) != allow) return -1;

        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += (pxor[i] | allow) == allow;
        }
        return cnt;
    };

    int ans = check(x);
    for (int b = 0; b < 30; b++) {
        if (((x >> b) & 1) == 0) continue;

        int c = (x ^ (1 << b)) | ((1 << b) - 1);
        ans = max(ans, check(c));
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}