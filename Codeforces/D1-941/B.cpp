#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;

    vector<int> ans;

    if (k == 1) {
        ans.push_back(3);
        for (int i = 1; i <= 24; i++)
            ans.push_back(1 << i);
    } else {
        int curr = 1;
        int sum = 0;

        while (sum + curr < k) {
            sum += curr;
            ans.push_back(curr);

            curr *= 2;
        }

        if (sum != k - 1)
            ans.push_back(k - 1 - sum);

        ans.push_back(k + 1);
        ans.push_back(3 * k);

        curr = 2 * k;
        while (ans.size() < 25 && curr <= 1e9) {
            ans.push_back(curr);
            curr *= 2;
        }
    }

    cout << ans.size() << '\n';
    for (auto x: ans) cout << x << " "; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}