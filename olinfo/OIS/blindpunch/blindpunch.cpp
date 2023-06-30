#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K; scanf("%d %d", &N, &K);
    priority_queue<pair<double, double>> P;

    for (int i = 0; i < N; i++) {
        double p; scanf("%lf", &p);
        P.push({p, 1 - p});
    }

    double ans = 0.;
    while (K--) {
        auto [top, scale] = P.top(); P.pop();
        ans += top;
        P.push({top * scale, scale});
    }

    ans = floor(ans * 1000000) / 1000000;
    printf("%.6lf\n", ans);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        solve();
    }
}