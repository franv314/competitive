#include<bits/stdc++.h>
using namespace std;

void scavi(
    int R, int C, int Q,
    vector<int> &x1, vector<int> &y1, vector<int> &x2, vector<int> &y2, vector<int> &P,
    vector<vector<int>> &terreno
) {
    vector<vector<int>> ps(R + 1, vector<int>(C + 1));
    for (int i = 0; i < Q; i++) {
        ps[x1[i]][y1[i]] += P[i];
        ps[x1[i]][y2[i] + 1] -= P[i];
        ps[x2[i] + 1][y1[i]] -= P[i];
        ps[x2[i] + 1][y2[i] + 1] += P[i];
    }

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            terreno[r][c] = ps[r][c]
                + (r != 0 ? terreno[r - 1][c] : 0)
                + (c != 0 ? terreno[r][c - 1] : 0)
                - (r != 0 && c != 0 ? terreno[r - 1][c - 1] : 0);
        }
    }
}