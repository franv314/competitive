#include <bits/stdc++.h>
using namespace std;

#define MAXR 10
#define MAXC 7
#define GET(bitmask, pos) (bitmask & (1 << (pos)))
#define BAD(line, given) ((line & given) != given)
#define _ << " " <<

int best[10][64][64];

int count(int row) {
    int c = 0;
    for (int i = 0; i < 6; i++) c += !!GET(row, i);
    return c;
}

bool tris(int row_1, int row_2, int row_3, int C) {
    for (int i = 0; i < C; i++)
        if (GET(row_1, i) && GET(row_2, i) && GET(row_3, i)) return true;
    for (int i = 0; i < C - 2; i++)
        if (GET(row_1, i) && GET(row_2, i + 1) && GET(row_3, i + 2)) return true;
    for (int i = 2; i < C; i++)
        if (GET(row_1, i) && GET(row_2, i - 1) && GET(row_3, i - 2)) return true;
    for (int i = 0; i < C - 2; i++) {
        if (GET(row_1, i) && GET(row_1, i + 1) && GET(row_1, i + 2)) return true;
        if (GET(row_2, i) && GET(row_2, i + 1) && GET(row_2, i + 2)) return true;
        if (GET(row_3, i) && GET(row_3, i + 1) && GET(row_3, i + 2)) return true;
    }
    return false;
}

int gioca(int N, int M, vector<int> g) {
    if (N * M == 1) return 1;

    auto [C, R] = minmax(N, M);
    int full_row = 1 << C;

    for (int r = R - 3; r >= 0; r--) {
        for (int row_1 = 0; row_1 < full_row; row_1++) {
            if (BAD(row_1, g[r])) continue;
            for (int row_2 = 0; row_2 < full_row; row_2++) {
                if (BAD(row_2, g[r + 1])) continue;
                for (int row_3 = 0; row_3 < full_row; row_3++) {
                    if (BAD(row_3, g[r + 2]) || tris(row_1, row_2, row_3, C)) continue;
                    best[r][row_1][row_2] = max(best[r][row_1][row_2], best[r + 1][row_2][row_3] + count(row_3));
                }
            }
        }
    }

    int ma = 0;
    for (int row_1 = 0; row_1 < full_row; row_1++) {
        if (BAD(row_1, g[0])) continue;
        for (int row_2 = 0; row_2 < full_row; row_2++) {
            if (BAD(row_2, g[1]) || tris(0, row_1, row_2, C)) continue;
            ma = max(ma, count(row_1) + count(row_2) + best[0][row_1][row_2]);
        }
    }
    return ma;
}

void symm(vector<vector<int>>& g) {
    int n = g.size(), m = g[0].size();
    vector<vector<int>> ret(m, vector<int>(n));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++)
            ret[j][i] = g[i][j];
    g = ret;
}

int main() {
    int N, M;
    cin >> N >> M;
    assert(cin.good());

    vector<vector<int>> G(N, vector<int>(M));
    for(auto& x : G)
        for(auto& y : x)
            cin >> y;
    assert(cin.good());

    vector<int> g(max(N, M));
    if (N > M) {
        for (int i = 0; i < N; i++)
            for (auto y: G[i])
                g[i] = (2 * g[i]) + y;
    } else {
        symm(G);
        for (int i = 0; i < M; i++)
            for (auto y: G[i])
                g[i] = (2 * g[i]) + y;
    }

    int c = 0;
    for (auto x: g) c += count(x);

    cout << gioca(N, M, g) - c << endl;
}