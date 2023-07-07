#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

void solve() {
    int n, d, h; cin >> n >> d >> h;
    vector<int> p(n);
    for (auto &x: p) cin >> x;
    
    long double area = 0.;
    long double a = 1.0 * d * h / 2;
    for (int i = 0; i < n; i++) {
        if (i + 1 == n || p[i + 1] >= p[i] + h) {
            area += a;
        } else {
            double h2 = 1.0 * (p[i + 1] - p[i] - h) / h;
            area += a - h2 * h2 * a; 
        }
    }
    cout << area << '\n';
}

int main() {
    cout << fixed << setprecision(15);
    int t; cin >> t;
    while (t--) solve();
}