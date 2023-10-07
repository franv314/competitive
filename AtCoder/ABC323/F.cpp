#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t xa, ya, xb, yb, xc, yc; cin >> xa >> ya >> xb >> yb >> xc >> yc;

    if (yb == yc) {
        swap(xa, ya);
        swap(xb, yb);
        swap(xc, yc);
    }
    if (xb == xc) {
        if (yc > yb) {
            cout << yc - yb + abs(xa - xb) + abs(ya - (yb - 1)) + 2 * (xa == xb && ya > yb) << '\n';
            return;
        } else {
            cout << yb - yc + abs(xa - xb) + abs(ya - (yb + 1)) + 2 * (xa == xb && ya < yb) << '\n';
            return;
        }
    }

    int64_t dist1, dist2;
    if (xb < xc) {
        dist1 = abs(xa - (xb - 1)) + abs(ya - yb);
        if (ya == yb && xa > xb) dist1 += 2;
    } else {
        dist1 = abs(xa - (xb + 1)) + abs(ya - yb);
        if (ya == yb && xa < xb) dist1 += 2;
    }
    if (yb < yc) {
        dist2 = abs(ya - (yb - 1)) + abs(xa - xb);
        if (xa == xb && ya > yb) dist2 += 2;
    } else {
        dist2 = abs(ya - (yb + 1)) + abs(xa - xb);
        if (xa == xb && ya < yb) dist2 += 2;
    }

    cout << abs(xb - xc) + abs(yb - yc) + 2 + min(dist1, dist2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int64_t t = 1;
    while (t--) solve();
}