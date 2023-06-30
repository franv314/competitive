#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto &x: p) cin >> x;

    long long sum = accumulate(p.begin(), p.end(), 0ll);
    long long mi = LLONG_MAX;

    for (int i = 0; i < (1 << n); i++) {
        long long a = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                a += p[j];
            }
        }
        long long b = sum - a;
        mi = min(mi, abs(b - a));
    }
    cout << mi;
}