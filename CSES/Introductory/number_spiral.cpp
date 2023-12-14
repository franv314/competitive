#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        int y, x; cin >> y >> x;

        int circle = max(x, y);
        int pos = y >= x ? x : 2 * circle - y;

        if (circle % 2 == 0) {
            pos = 2 * circle - pos;
        }

        cout << (long long)(circle - 1) * (circle - 1) + pos << "\n";
    }
}