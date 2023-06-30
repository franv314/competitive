#include <bits/stdc++.h>
using namespace std;

#define MAXN 1800

struct MySet {
    tuple<short, short, bool> a[3];

    void insert(tuple<short, short, bool> b) {
        if (a[0] == b || a[1] == b || a[2] == b) return;
        
        if (get<0>(a[0]) == -1) {
            a[0] = b;
            return;
        }
        if (get<0>(a[1]) == -1) {
            a[1] = b;
            return;
        }
        if (get<0>(a[2]) == -1) {
            a[2] = b;
            return;
        }
        assert(false);
    }

    void erase(tuple<short, short, bool> b) {
        if (a[0] == b) {
            a[0] = {-1, -1, 0};
            return;
        }
        if (a[1] == b) {
            a[1] = {-1, -1, 0};
            return;
        }
        if (a[2] == b) {
            a[2] = {-1, -1, 0};
            return;
        }
        assert(false);
    }

    MySet() {
        a[0] = a[1] = a[2] = {-1, -1, 0};
    }
};

MySet adj[MAXN][MAXN][2];
pair<long long, tuple<short, short, bool>> best[MAXN][MAXN][2];
bool queued[MAXN][MAXN][2];
int grid[MAXN][MAXN];

int main() {
    int N, M; cin >> N >> M;
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < M; j++) {
            if (i < N - 1) adj[i][j][1].insert({i + 1, j, 0});
            if (j < M - 1) adj[i][j][1].insert({i, j + 1, 0});

            adj[i][j][0].insert({i, j, 1});
            cin >> grid[i][j];
        }
    }

    long long total = 0;

    for (int _ = 0; _ < 2; _++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                best[i][j][0] = best[i][j][1] = {1e18, {-1, -1, -1}};
                queued[i][j][0] = queued[i][j][1] = false;
            }
        }
        
        best[0][0][1].first = 0;

        queue<tuple<short, short, bool>> q;
        q.push({0, 0, 1});
        queued[0][0][1] = true;

        while (!q.empty()) {
            auto [i, j, t] = q.front(); q.pop();
            queued[i][j][t] = false;
            for (auto [in, jn, tn]: adj[i][j][t].a) {
                if (in == -1) continue;
                int weight = 0;
                if (in == i && jn == j) weight = (t == 0 ? -grid[i][j] : grid[i][j]);

                if (best[in][jn][tn].first > best[i][j][t].first + weight) {
                    best[in][jn][tn] = {best[i][j][t].first + weight, {i, j, t}};
                    if (!queued[in][jn][tn]) q.push({in, jn, tn});
                }
            }
        }
        total -= best[N - 1][M - 1][0].first;
        int curr_i = N - 1, curr_j = M - 1, curr_t = 0;
        while (curr_i != 0 || curr_j != 0 || curr_t != 1) {
            auto [next_i, next_j, next_t] = best[curr_i][curr_j][curr_t].second;
            adj[next_i][next_j][next_t].erase({curr_i, curr_j, curr_t});
            adj[curr_i][curr_j][curr_t].insert({next_i, next_j, next_t});

            curr_i = next_i, curr_j = next_j, curr_t = next_t;
        }
    }
    cout << total;
}