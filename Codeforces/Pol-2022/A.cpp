#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int curr = -1;
        s.erase(s.begin());
        for (auto x: s) {
            if (x == '1') {
                cout << (curr == 1 ? '+' : '-');
                curr *= -1;
            } else {
                cout << "+";
            }
        }
        cout << endl;
    }
}