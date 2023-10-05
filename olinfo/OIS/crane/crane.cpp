#include <bits/stdc++.h>
using namespace std;

#define MAXR 500
#define MAXL 101'001
#define INF 1e18

struct MapWrapper {
    unordered_map<int, long long> map;

    long long& operator[](const int &idx) {
        if (!map.count(idx)) map[idx] = 1e18;
        return map[idx];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int D, N; cin >> D >> N;
    D += MAXR;
    vector<int> X(N), R(N), T(N), K(N), dir(N);

    for (int i = 0; i < N; i++) {
        cin >> X[i] >> R[i] >> T[i] >> K[i] >> dir[i];
        X[i] += MAXR;
    }

    vector<long long> dst(MAXL, INF);
    dst[MAXR] = 0;

    for (int i = 0; i < N; i++) {
        vector<long long> new_dst = dst;
        for (int l = X[i] - R[i]; l <= X[i] + R[i]; l++) {
            for (int r = X[i] - R[i]; r <= X[i] + R[i]; r++) {
                if (l == r || l == X[i] || r == X[i]) continue;
                
                long long cost1 = (dir[i] ^ (l > X[i])) * T[i] + (R[i] - abs(l - X[i])) * (long long)K[i];
                long long cost2 = ((r > X[i]) ^ (l > X[i])) * T[i] + abs(abs(r - X[i]) - abs(l - X[i])) * (long long)K[i];

                new_dst[r] = min(new_dst[r], dst[l] + cost1 + cost2);
            }
        }
        dst = new_dst;
    }

    cout << dst[D] << '\n';
}