#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    long long l = 0, r = accumulate(a.begin(), a.end(), 0ll);
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        
        vector<int> pref(n + 1), suff(n + 1);

        {
            priority_queue<int> biggest;
            long long sum = 0;
            int removed = 0;
            for (int i = 0; i < n; i++) {
                sum += a[i];
                biggest.push(a[i]);
                while (sum > m) {
                    sum -= biggest.top();
                    biggest.pop();
                    removed++;
                }
                pref[i + 1] = removed;
            }
        }
        {
            priority_queue<int> biggest;
            long long sum = 0;
            int removed = 0;
            for (int i = n - 1; i >= 0; i--) {
                sum += a[i];
                biggest.push(a[i]);
                while (sum > m) {
                    sum -= biggest.top();
                    biggest.pop();
                    removed++;
                }
                suff[n - i] = removed;
            }
        }
        bool ok = false;
        for (int i = 0; i <= n; i++) {
            if (pref[i] + suff[n - i] <= n - k) {
                ok = true;
                break;
            }
        }
        if (ok) r = m;
        else l = m;
    }
    cout << l + 1 << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}