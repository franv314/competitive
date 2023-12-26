#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    vector<int> pos_of(n + 1);
    pos_of[0] = INT_MAX;

    for (int i = 1; i <= n; i++) {
        int v; cin >> v;
        pos_of[v] = i;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += pos_of[i] < pos_of[i - 1];
    }

    cout << ans << '\n';
}