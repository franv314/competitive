#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<long long> px(n + 1);
    for (int i = 1; i <= n; i++) px[i] = px[i - 1] ^ a[i - 1];

    while (q--) {
        int l, r; cin >> l >> r;
        cout << (px[r] ^ px[l - 1]) << '\n';
    }
}