#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int taglia(int N, int V[]) {
    int max_cut[N];
    
    int r = 0;
    set<int> elems;
    for (int i = 0; i < N; i++) {
        while (r < N && elems.find(V[r]) == elems.end())
            elems.insert(V[r++]);
        max_cut[i] = r;
        elems.erase(V[i]);
    }

    vector<int> dp(N + 1), ss(N + 2);
    ss[N] = dp[N] = 1;
    for (int i = N - 1; i >= 0; i--) {
        dp[i] = (ss[i + 1] - ss[max_cut[i] + 1] + MOD) % MOD;
        ss[i] = (ss[i + 1] + dp[i]) % MOD;
    }
    return dp[0];
}