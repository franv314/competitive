#include <bits/stdc++.h>
using namespace std;

constexpr int B[] = {3, 5, 7, 11};
constexpr int b_cnt = sizeof(B) / sizeof(int);
constexpr int MOD = 950'188'441;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    vector<string> rotgrid(m, string(n, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            rotgrid[j][i] = grid[i][j];

    vector<vector<int>> pows(n, vector<int>(b_cnt, 1));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < b_cnt; j++) {
            pows[i][j] = (long long)pows[i - 1][j] * B[j] % MOD;
        }
    }

    map<array<int, b_cnt>, int> scores;
    map<array<int, b_cnt>, pair<int, int>> hash_to_case;
    for (int z = 0; z < m; z++) {
        string col = rotgrid[z];
        array<int, b_cnt> hash = {0, 0, 0, 0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b_cnt; j++) {
                hash[j] = (hash[j] + (long long)pows[i][j] * (col[i] - '0' + 1)) % MOD;
            }
        }

        for (int i = 0; i < n; i++) {
            array<int, b_cnt> nhash = hash;
            for (int j = 0; j < b_cnt; j++) {
                if (col[i] == '0') {
                    nhash[j] = (hash[j] + pows[i][j]) % MOD;
                } else {
                    nhash[j] = (hash[j] - pows[i][j] + MOD) % MOD;
                }
            }
            scores[nhash]++;
            hash_to_case[nhash] = {z, i};
        }
    }

    int best_score = -1;
    array<int, b_cnt> best;
    for (auto [hash, score]: scores) {
        if (score > best_score) {
            best_score = score;
            best = hash;
        }
    }

    cout << best_score << '\n';
    auto [col, row] = hash_to_case[best];
    for (int i = 0; i < n; i++) {
        cout << ((rotgrid[col][i] - '0') ^ (i == row));
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}