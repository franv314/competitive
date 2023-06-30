#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        
        cout << "? 1 1" << endl;
        int d1; cin >> d1;

        if (d1 + 1 <= m) {
            cout << "? 1 " << d1 + 1 << endl;
            int d2; cin >> d2;

            if (d2 != d1) {
                cout << "! " << d2 + 1 << " " << d1 + 1 << endl;
                continue;
            }
        }

        cout << "? " << d1 + 1 << " 1" << endl;
        int d3; cin >> d3;

        cout << "! " << d1 + 1 << " " << d3 + 1 << endl;
    }
}