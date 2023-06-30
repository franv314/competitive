#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        deque<int> a(n);
        for (auto &x: a) cin >> x;
        a.push_front(0);
        a.push_back(1440);

        int count = 0;
        for (int i = 0; i < n + 1; i++) {
            count += (a[i + 1] - a[i]) / 120;
        }
        cout << (count >= 2 ? "YES\n" : "NO\n");
    }
}