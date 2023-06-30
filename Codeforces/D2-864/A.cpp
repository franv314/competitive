#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;

        int a, b;
        if ((x1 == 1 || x1 == n) && (y1 == 1 || y1 == m)) a = 2;
        else if (x1 == 1 || x1 == n || y1 == 1 || y1 == m) a = 3;
        else a = 4;

        if ((x2 == 1 || x2 == n) && (y2 == 1 || y2 == m)) b = 2;
        else if (x2 == 1 || x2 == n || y2 == 1 || y2 == m) b = 3;
        else b = 4;

        cout << min(a, b) << "\n";
    }
}