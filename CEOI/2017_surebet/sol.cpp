#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    priority_queue<double> a, b;
    double sum_a = 0, sum_b = 0;
    for (int i = 0; i < n; i++) {
        double x, y; cin >> x >> y;
        a.push(x);
        b.push(y);
    }
    
    double ans = 0;
    for (int bet = 1; bet <= 2 * n; bet++) {
        if ((sum_a < sum_b && !a.empty()) || b.empty()) {
            sum_a += a.top(); a.pop();
        } else {
            sum_b += b.top(); b.pop();
        }
        ans = max(ans, min(sum_a, sum_b) - bet);
    }

    printf("%.4lf", ans);
}