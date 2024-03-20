#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<string> grid(N);
    for (auto &row: grid) cin >> row;
    
    int l = 1e9, r = -1e9, t = 1e9, b = -1e9;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '1') {
                t = min(t, i);
                b = max(b, i);
                l = min(l, j);
                r = max(r, j);
            }
        }
    }
    
    if (l == 1e9) return void(cout << "0\n");
    
    for (int i = t; i <= b; i++) {
        for (int j = l; j <= r; j++) {
            if (grid[i][j] == '0') return void(cout << "0\n");
        }
    }
    
    cout << "1\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
}