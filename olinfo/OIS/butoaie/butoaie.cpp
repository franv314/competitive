#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;
    int P, Q; cin >> P >> Q;

    vector<int> V(N);
    for (auto &v: V) cin >> v;

    if (P == Q) {
        int ma = *max_element(V.begin(), V.end());
        cout << (ma + P - 1) / P << '\n';
        return 0;
    }

    if (Q < P) {
        swap(P, Q);
    } else {
        K = N - K;
    }

    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        long long tot = 0;
        bool ok = true;
        for (auto v: V) {
            long long cnt = (v - (long long)m * P) <= 0 ? 0 : 1 + (v - (long long)m * P - 1) / (Q - P);
            if (cnt > m) ok = false;
            tot += cnt;
        }

        if (ok && tot <= (long long)m * K) r = m;
        else l = m;
    }

    cout << r << '\n';
}