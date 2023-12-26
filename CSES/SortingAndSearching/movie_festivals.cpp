#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<pair<int, int>> movies(n);

    for (auto &[b, a]: movies) {
        cin >> a >> b;
    }

    sort(movies.begin(), movies.end());
    int ans = 0;
    int t = -1;

    for (auto [b, a]: movies) {
        if (a < t) continue;
        ans++;
        t = b;
    }

    cout << ans << '\n';
}