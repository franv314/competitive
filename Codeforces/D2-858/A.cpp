#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        swap(a, b); swap(c, d);
        if (c < a) {
            cout << "-1\n";
            continue;
        }
        int steps = c - a;
        a += steps; b += steps;
        if (d > b) {
            cout << "-1\n";
            continue;
        }
        steps += b - d;
        cout << steps << "\n";
    }
}