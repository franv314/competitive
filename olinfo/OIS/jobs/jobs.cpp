#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<int> T(N), P(N);
    for (auto &x: T) cin >> x;
    for (auto &x: P) cin >> x;

    int sum = accumulate(T.begin(), T.end(), 0);
    vector<long long> best(sum + 1, 0);
    best[0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = T[i]; j <= sum; j++) {
            best[j] = max(best[j], P[i] + best[j - T[i]]);
        }
    }

    if (M <= sum) {
        cout << best[M] << '\n';
        return 0;
    }

    long long ma = -1;
    int rem = M - sum;
    for (int i = 0; i < N; i++) {
        int cnt = (rem + T[i] - 1) / T[i];
        ma = max(ma, (long long)cnt * P[i] + best[M - cnt * T[i]]);
    }

    cout << ma << '\n';
}