#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;


void solve() {
    int N; cin >> N;
    deque<int> A(N);
    for (auto &a: A) cin >> a;
    A.push_front(-1);

    vector<int> pows(N + 1);
    pows[0] = 1;
    for (int i = 1; i <= N; i++)
        pows[i] = (pows[i - 1] * 2) % MOD;

    vector<vector<int>> divs(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            divs[j].push_back(i);
        }
    }

    vector<int> pos(N);
    iota(pos.begin(), pos.end(), 1);
    sort(pos.begin(), pos.end(), [&](int a, int b) { return A[a] > A[b]; });

    int no = 0;
    vector<bool> used(N + 1);
    long long tot = 0;

    for (auto p: pos) {
        int any = 0;
        for (auto div: divs[p]) {
            if (!used[div]) any++;
        }

        int others = N - no - any;

        tot += (long long)A[p] * pows[others] % MOD * (pows[any] - 1) % MOD;
        tot %= MOD;


        for (auto div: divs[p]) {
            if (!used[div]) {
                used[div] = true;
                no++;
            }
        }
    }

    cout << tot << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}