#include <bits/stdc++.h>
using namespace std;

long long diff(vector<int> a, vector<int> b) {
    long long ret = 0;
    for (int i = 0; i < a.size(); i++)
        ret += abs(a[i] - b[i]);
    return ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        vector<int> a(2 * n);
        for (auto &x: a) cin >> x;
        sort(a.begin(), a.end());
        if (n == 1) {
            cout << abs(a[1] - a[0]) << "\n";
            continue;
        }

        
        long long ans = diff(a, vector<int>(2 * n, 0));
        if (n % 2 == 0) {
            vector<int> test(2 * n, -1);
            test[2 * n - 1] = n;
            ans = min(ans, diff(a, test));
        }
        if (n == 2) {
            ans = min(ans, diff(a, vector<int>({2, 2, 2, 2})));
        }
        cout << ans << "\n";
    }
}