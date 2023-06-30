#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int a1, a2, b1, b2, c1, c2;
        cin >> a1 >> a2;
        cin >> b1 >> b2;
        cin >> c1 >> c2;
        cout << "case #" << i + 1 << ": " << min({a2, b2, c2}) - max({a1, b1, c1}) << endl;
    }
}