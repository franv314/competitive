#include <bits/stdc++.h>
using namespace std;

typedef uint64_t hash_t;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, m, k; cin >> n >> m >> k;
    n++, m++;
    mt19937_64 rng;
    vector<hash_t> hashes(k);
    
    for (auto &hash: hashes) {
        hash = rng();
    }
    
    vector<vector<hash_t>> grid(n, vector<hash_t>(m)), pxor(n + 1, vector<hash_t>(m + 1));
    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        grid[x1][y1] ^= hashes[i];
        grid[x2][y2] ^= hashes[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pxor[i + 1][j + 1] = pxor[i + 1][j] ^ pxor[i][j + 1] ^ pxor[i][j] ^ grid[i][j];
        }
    }
    
    int64_t total = 0;
    
    for (int l = 0; l < n; l++) {
        for (int r = l + 2; r <= n; r++) {
            unordered_map<hash_t, int> cnt;
            for (int h = 1; h <= m; h++) {
                cnt[pxor[l][h] ^ pxor[r][h]]++;
            }
            
            for (int h = 0; h < m; h++) {
                cnt[pxor[l][h + 1] ^ pxor[r][h + 1]]--;
                total += cnt[pxor[l][h] ^ pxor[r][h]];
            }
        }
    }
    
    cout << total << '\n';
}
