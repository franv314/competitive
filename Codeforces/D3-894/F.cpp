#include <bits/stdc++.h>
using namespace std;

template<int len = 1>
vector<bool> solve(int size, vector<int> &weights) {
    if (len - 1 < size) {
        return solve<min(len * 2, 2'000'000)>(size, weights);
    }

    bitset<len> found;
    found.set(0);
    for (auto w: weights) {
        found |= (found << w);
    }

    vector<bool> ans(size);
    for (int i = 0; i < size; i++) {
        ans[i] = found[i];
    }
    return ans;
}

void solve() {
    int w, f; cin >> w >> f;
    int n; cin >> n;
    vector<int> weights(n);
    for (auto &x: weights) cin >> x;

    int total = accumulate(weights.begin(), weights.end(), 0);
    vector<bool> found = solve(total + 1, weights);

    int ans = INT_MAX;
    for (int i = 0; i <= total; i++) {
        if (!found[i]) continue;
        
        int cost = max((i + w - 1) / w, (total - i + f - 1) / f);
        ans = min(ans, cost);
    }
    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}