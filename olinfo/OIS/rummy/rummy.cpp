#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void solve() {
    int N; cin >> N;
    vector<i64> A(N + 2);
    for (auto &x: A) cin >> x;

    for (int _: {0, 1})
        for (int i = 1; i < N + 2; i++)
            A[i] += A[i - 1];

    i64 max_slope = -1, max_height = 0;
    for (int i = 0; i < N; i++) {
        i64 slope = (A[i] + i) / (i + 1);
        i64 height = A[i] + slope * (N - i);
    
        max_slope = max(slope, max_slope);
        max_height = max(height, max_height);
    }

    if (max_height > A[N] || max_slope > A[N + 1] - A[N])
        cout << "NO\n";
    else
        cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
}
