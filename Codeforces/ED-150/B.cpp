#include <bits/stdc++.h>
using namespace std;

void solve() {
    int q; cin >> q;
    bool flag = false;

    int begin; cin >> begin;
    cout << '1';
    int back = begin;
    
    while (--q) {
        int x; cin >> x;
        if (!flag) {
            if (x >= back) {
                back = x;
                cout << '1';
            } else if (x <= begin) {
                back = x;
                cout << '1';
                flag = true;
            } else {
                cout << '0';
            }
        } else {
            if (x >= back && x <= begin) {
                back = x;
                cout << '1';
            } else {
                cout << '0';
            }
        }
    }
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}