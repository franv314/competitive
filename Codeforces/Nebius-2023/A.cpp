#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        a = abs(a), b = abs(b);
        if (a < b) swap(a, b);
        int x = 2 * b;
        if (a != b) x += 2 * (a - b) - 1;
        cout << x << "\n";
    }
}