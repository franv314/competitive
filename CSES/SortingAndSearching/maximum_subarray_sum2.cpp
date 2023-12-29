#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, a, b; cin >> n >> a >> b;
    vector<int> x(n);
    for (auto &y: x) cin >> y;

    vector<long long> ps(n + 1);
    for (int i = 0; i < n; i++) ps[i + 1] = ps[i] + x[i];

    multiset<long long> ends;
    long long ma = LLONG_MIN;
    for (int i = n - a; i >= 0; i--) {
        ends.insert(ps[i + a]);
        if (i + b + 1 <= n) ends.erase(ends.find(ps[i + b + 1]));

        ma = max(ma, *ends.rbegin() - ps[i]);
    }

    cout << ma << '\n';
}