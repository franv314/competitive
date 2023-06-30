#include <bits/stdc++.h>
using namespace std;

#define MAXN 500'001

const int MOD = 1e9 + 7;
map<int, int> amounts[MAXN];

int main() {
    int N, M; cin >> N >> M;
    
    vector<tuple<int, int, int>> edges(M);
    for (auto &[c, a, b]: edges) cin >> a >> b >> c;

    sort(edges.rbegin(), edges.rend());
    for (auto [c, a ,b]: edges) {
        amounts[a][c - 1] = (amounts[a][c - 1] + amounts[b][c] + 1) % MOD;
        amounts[b][c - 1] = (amounts[b][c - 1] + amounts[a][c] + 1) % MOD;
    }

    int total = 0;
    for (int i = 1; i <= N; i++) {
        for (auto [_, n]: amounts[i]) {
            total = (total + n) % MOD;
        }
    }

    cout << (total - M + MOD) % MOD << endl;
    return 0;
}