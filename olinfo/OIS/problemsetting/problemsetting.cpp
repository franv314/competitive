#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long N; cin >> N;
    vector<long long> A(N), B(N - 1);
    for (auto &x: A) cin >> x;
    for (auto &x: B) cin >> x;
    B.push_back(0);

    auto check = [&](long long m) -> bool {
        long long rem = 0;
        for (long long i = 0; i < N; i++) {
            long long need = max(0LL, m - A[i] - rem);

            rem = B[i] - need;
            if (rem < 0)
                return false;
        }

        return true;
    };

    long long l = 0, r = 1e18;
    while (r - l > 1) {
        long long m = (l + r) / 2;

        if (check(m)) l = m;
        else r = m;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    long long t; cin >> t;
    while (t--) solve();
}