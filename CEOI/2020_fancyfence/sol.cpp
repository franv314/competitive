#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<int> H(N), W(N);
    for (auto &h: H) cin >> h;
    for (auto &w: W) cin >> w;

    vector<int> ps(N + 1);
    for (int i = 0; i < N; i++) ps[i + 1] = (ps[i] + W[i]) % MOD;

    int ans = 0;
    stack<int> st;
    for (int i = 0; i < N; i++) {
        while (!st.empty() && H[st.top()] >= H[i]) {
            int lst = st.top(); st.pop();

            int max_h = H[lst];
            int min_h = max(H[i], st.empty() ? 0 : H[st.top()]);
            int dw = (ps[i] - (st.empty() ? 0 : ps[st.top() + 1]) + MOD) % MOD;

            int wc = ((long long)dw * (dw + 1) / 2) % MOD;
            int hc = ((long long)max_h * (max_h + 1) / 2 - (long long)min_h * (min_h + 1) / 2) % MOD;
            int ch = (long long)wc * hc % MOD;

            ans = (ans + ch) % MOD;
        }

        st.push(i);
    }

    while (!st.empty()) {
        int lst = st.top(); st.pop();

        int max_h = H[lst];
        int min_h = st.empty() ? 0 : H[st.top()];
        int dw = (ps.back() - (st.empty() ? 0 : ps[st.top() + 1]) + MOD) % MOD;

        int wc = ((long long)dw * (dw + 1) / 2) % MOD;
        int hc = ((long long)max_h * (max_h + 1) / 2 - (long long)min_h * (min_h + 1) / 2) % MOD;
        int ch = (long long)wc * hc % MOD;

        ans = (ans + ch) % MOD;
    }

    cout << ans << '\n';
}