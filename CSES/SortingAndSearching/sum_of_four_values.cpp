#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, pair<int, int>> sums;

    for (int i = n - 3; i >= 0; i--) {
        for (int j = i + 2; j < n; j++) {
            sums[a[i + 1] + a[j]] = {i + 1, j};
        }

        for (int j = 0; j < i; j++) {
            if (sums.count(x - a[i] - a[j])) {
                auto [k, l] = sums[x - a[i] - a[j]];
                cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << ' ' << l + 1 << '\n';
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}