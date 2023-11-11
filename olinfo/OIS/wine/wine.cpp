#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N, K; cin >> N >> K;
    K--;

    vector<int> arr(N);
    for (auto &x: arr) cin >> x;

    vector<long long> ps(N + 1);
    for (int i = 0; i < N; i++) ps[i + 1] = ps[i] + arr[i];

    long long l = 0, r = 1 + ps[N];
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        long long cnt = 0;
        for (auto it = ps.begin(); it != ps.end(); it++) {
            cnt += lower_bound(it, ps.end(), m + *it) - it - 1;
        }

        if (cnt > K) r = m;
        else l = m;
    }

    long long cnt = 0;
    for (auto it = ps.begin(); it != ps.end(); it++) {
        cnt += lower_bound(it, ps.end(), l + *it) - it - 1;
    }

    for (int i = 0; i < N; i++) {
        auto it = lower_bound(ps.begin(), ps.end(), l + ps[i]);
        if (it != ps.end() && *it == l + ps[i]) {
            if (cnt++ == K) {
                cout << i << " " << it - 1 - ps.begin() << '\n';
                break;
            }
        }
    }
}