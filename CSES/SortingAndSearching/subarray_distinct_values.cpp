#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long ans = 0;
    int r = 0;
    map<int, int> values;
    for (int l = 0; l < n; l++) {
        while (r != n && values.size() < k || values.count(a[r])) {
            values[a[r]]++;
            r++;
        }
        ans += r - l;

        if (--values[a[l]] == 0) values.erase(a[l]);
    }

    cout << ans << '\n';
}