#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    
    double ev = 0;

    for (int ma = 1; ma <= k; ma++) {
        double p = pow((double)ma / k, n) - pow((double)(ma - 1) / k, n);
        ev += p * ma;
    }

    printf("%.6f\n", ev);
}