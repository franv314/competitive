#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> p(n);
    for (auto &x: p) cin >> x;

    priority_queue<long long> pq;
    long long lazy = 0;
    pq.push(0); 
    pq.push(-1e18);

    for (auto x: p) {
        lazy += x;
        pq.push(-lazy);
        pq.push(-lazy);

        pq.pop();
    }

    vector<long long> slopes;
    while (pq.size() > 1) {
        slopes.push_back(pq.top());
        pq.pop();
    }
    reverse(slopes.begin(), slopes.end());

    long long tot = 0;
    for (int i = 0; i < n; i++) {
        tot += (i + 1LL) * p[i];
    }

    for (auto slope: slopes) {
        tot -= (slope + lazy);
    }

    cout << tot << '\n';
}