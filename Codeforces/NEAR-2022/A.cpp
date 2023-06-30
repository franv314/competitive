#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;

    while (t--) {
        int n, m; cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) {
            int b; cin >> b;
            auto it = min_element(a.begin(), a.end());
            *it = b;
        }
        cout << accumulate(a.begin(), a.end(), 0ll) << endl;
    }
}