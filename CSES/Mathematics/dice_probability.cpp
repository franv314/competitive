#include <bits/stdc++.h>
using namespace std;

typedef long double f80;

int main() {
    int n, a, b; scanf("%d%d%d", &n, &a, &b);

    vector<vector<f80>> ways(n + 1, vector<f80>(6 * n + 1));
    ways[0][0] = 1.0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6 * n; j++) {
            for (int k = max(j - 6, 0); k < j; k++) {
                ways[i][j] += ways[i - 1][k] / 6.0;
            }
        }
    }

    f80 ans = accumulate(ways[n].begin() + a, ways[n].begin() + b + 1, 0.0L);
    printf("%.6Lf\n", ans);
}