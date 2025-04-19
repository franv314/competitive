#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 160;
constexpr int MAXT = 160;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int L, N, T; cin >> L >> N >> T;
    vector<pair<int, int>> points(N);
    for (auto &[x, y]: points) {
        cin >> x >> y;
        x--, y--;
    }
    
    auto d1 = [&](const pair<int, int> &p) { return 2 * (p.first + p.second); };
    auto d2 = [&](const pair<int, int> &p) { return 2 * (p.first + (L - 1 - p.second)); };
    auto d3 = [&](const pair<int, int> &p) { return 2 * ((L - 1 - p.first) + p.second); };
    auto d4 = [&](const pair<int, int> &p) { return 2 * ((L - 1 - p.first) + (L - 1 - p.second)); };

    vector nxt(T + 1, vector(T + 1, vector(T + 1, 0)));
    vector prv(T + 1, vector(T + 1, vector(T + 1, (int)1e9)));

    prv[0][0][0] = 0;
    for (int i = 0; i < N; i++) {

        int D1 = d1(points[i]);
        int D2 = d2(points[i]);
        int D3 = d3(points[i]);
        int D4 = d4(points[i]);

        for (int j = 0; j <= T; j++) {
            for (int k = 0; k <= T; k++) {
                for (int l = 0; l <= T; l++) {
                    nxt[j][k][l] = prv[j][k][l] + D4;
                    if (j >= D1) {
                        nxt[j][k][l] = min(nxt[j][k][l], prv[j - D1][k][l]);
                    }
                    if (k >= D2) {
                        nxt[j][k][l] = min(nxt[j][k][l], prv[j][k - D2][l]);
                    }
                    if (l >= D3) {
                        nxt[j][k][l] = min(nxt[j][k][l], prv[j][k][l - D3]);
                    }
                }
            }
        }

        prv = nxt;
    }

    for (int i = 0; i <= T; i++) {
        for (int j = 0; j <= T; j++) {    
            for (int k = 0; k <= T; k++) {
                if (prv[i][j][k] <= T) {
                    cout << "Yes\n";
                    return 0;
                }
            }   
        }   
    }

    cout << "No\n";
}