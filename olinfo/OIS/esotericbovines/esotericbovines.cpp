#include <bits/stdc++.h>
using namespace std;

long long solve(int N, long long K, vector<long long> &A, vector<long long> &B) {
    vector<pair<vector<long long>, vector<long long>>> groups;
    groups.emplace_back(A, B);

    long long ans = 0;
    long long acc = 0;

    for (int bit = 60; bit >= 0; bit--) {
        vector<pair<vector<long long>, vector<long long>>> hi_groups, lo_groups;
        long long lo = 0;

        for (auto &[a, b]: groups) {
            vector<long long> a0, a1, b0, b1;
            for (auto x: a) {
                if ((x >> bit) & 1) a1.push_back(x);
                else a0.push_back(x);
            }
            for (auto x: b) {
                if ((x >> bit) & 1) b1.push_back(x);
                else b0.push_back(x);
            }

            if (a0.size() && b1.size()) {
                hi_groups.emplace_back(a0, b1);
            }
            if (a1.size() && b0.size()) {
                hi_groups.emplace_back(a1, b0);
            }

            if (a0.size() && b0.size()) {
                lo_groups.emplace_back(a0, b0);
                lo += (long long)a0.size() * b0.size();
            }
            if (a1.size() && b1.size()) {
                lo_groups.emplace_back(a1, b1);
                lo += (long long)a1.size() * b1.size();
            }
        }

        if (acc + lo < K) {
            acc += lo;
            groups = hi_groups;

            ans |= 1LL << bit;
        } else {
            groups = lo_groups;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        long long K; cin >> K;

        vector<long long> A(N), B(N);
        for (auto &x: A) cin >> x;
        for (auto &x: B) cin >> x;

        cout << solve(N, K, A, B) << '\n';
    }
}