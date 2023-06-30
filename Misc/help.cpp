#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

ifstream in("help.in");
ofstream out("help.out");

int main() {
    int N; in >> N;
    vector<int> state(2 * N);
    for (int i = 0; i < N; i++) {
        int l, r; in >> l >> r;
        l--, r--;
        state[l] = 1;
        state[r] = -1;
    }
    
    vector<int> pows(N + 1, 1);
    for (int i = 1; i <= N; i++) {
        pows[i] = 2 * pows[i - 1] % MOD;
    }
    
    int curr = 0;
    int ans = 0;
    for (auto x: state) {
        curr += x;
        if (x == 1) (ans += pows[N - curr]) %= MOD;
    }
    out << ans;
}