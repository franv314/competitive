#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    long long ans = 0;
    vector<int> a(n);

    for (auto &x: a) {
        cin >> x;
        int y; cin >> y;
        ans += y;
    }

    sort(a.begin(), a.end());
    long long ps = 0;
    for (auto x: a) {
        ps += x;
        ans -= ps;
    }

    cout << ans << '\n';
}