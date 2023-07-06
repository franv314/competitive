#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define MAXM 1000

enum dir_t { R, C };

ifstream in("input.txt");
ofstream out("output.txt");

pair<int, pair<dir_t, int>> dp[MAXN + 1][MAXM][2];

ostream& operator<<(ostream& out, dir_t d) {
    return out << (d == R ? 'R' : 'C');
}

int main() {
    int N, M; in >> N >> M;
    vector<pair<int, int>> events(N);
    for (auto &[r, c]: events) {
        in >> r >> c;
        r--, c--;
    }
    
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < M; j++) {
            auto [r, c] = events[i];
            { // Row just moved
                int pos_c = j;
                int pos_r = i ? events[i - 1].first : 0;

                int cost_c = abs(pos_c - c) + dp[i + 1][pos_r][C].first;
                int cost_r = abs(pos_r - r) + dp[i + 1][pos_c][R].first;
                if (cost_c < cost_r) {
                    dp[i][j][R] = {cost_c, {C, pos_r}};
                } else {
                    dp[i][j][R] = {cost_r, {R, pos_c}};
                }
            }
            { // Col just moved
                int pos_c = i ? events[i - 1].second : 0;
                int pos_r = j;

                int cost_c = abs(pos_c - c) + dp[i + 1][pos_r][C].first;
                int cost_r = abs(pos_r - r) + dp[i + 1][pos_c][R].first;
                if (cost_c < cost_r) {
                    dp[i][j][C] = {cost_c, {C, pos_r}};
                } else {
                    dp[i][j][C] = {cost_r, {R, pos_c}};
                }
            }
        }
    }
    
    pair<dir_t, int> state = {R, 0};
    for (int i = 0; i < N; i++) {
        out << dp[i][state.second][state.first].second.first << '\n';
        state = dp[i][state.second][state.first].second;
    }
}