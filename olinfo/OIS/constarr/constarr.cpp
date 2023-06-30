#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long N;
int M, L, R, K;

int main() {
    cin >> N >> M >> L >> R >> K;
    
    vector<long long> curr(M);
    for (int i = 0; i < M; i++) {
        int l = L / M * M + i;
        int r = R / M * M + i;
        if (l < L) l += M;
        if (r <= R) r += M;
        curr[i] = (r - l) / M;
    }
    vector<long long> ans(M);
    ans[0] = 1;

    for (; N; N >>= 1) {
        if (N & 1) {
            vector<long long> nans(M);
            for (int m = 0; m < M; m++) {
                for (int i = 0; i < M; i++) {
                    nans[m] = (nans[m] + ans[i] * curr[(m - i + M) % M]) % MOD;
                }
            }
            ans = nans;
        }
        vector<long long> ncurr(M);
        for (int m = 0; m < M; m++) {
            for (int i = 0; i < M; i++) {
                ncurr[m] = (ncurr[m] + curr[i] * curr[(m - i + M) % M]) % MOD;
            }
        }
        curr = ncurr;
    }
    cout << ans[K] << endl;
}