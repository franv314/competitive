#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, K; cin >> N >> K;
    vector<int> seqs(N + 1);
    seqs[0] = K;
    long long ans = 1;
    while (N--) {
        int S; cin >> S;
        ans = (ans * seqs[S]) % MOD;
        seqs[S]--;
        seqs[S + 1]++;
    }
    cout << ans;
}