#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    rotate(a.begin(), next(find(a.begin(), a.end(), 0)), a.end());

    long long val = 0;
    long long ma = 0;
    stack<pair<int, int>> st;
    st.emplace(0, -1);

    for (int i = 0; i < n - 1; i++) {
        while (a[i] < st.top().first) {
            auto [val_1, pos_1] = st.top(); st.pop();
            auto [val_2, pos_2] = st.top();

            val -= val_1 * (long long)(pos_1 - pos_2);
        }

        auto [val_2, pos_2] = st.top();
        val += a[i] * (long long)(i - pos_2);
        st.emplace(a[i], i);

        ma = max(ma, val);
    }

    cout << ma + n << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}