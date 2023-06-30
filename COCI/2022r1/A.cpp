// Task "Desni klik"

#include <bits/stdc++.h>
using namespace std;

int n, r, s;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> r >> s;
    while (n--) {
        int ma = INT_MIN, mi = INT_MAX;
        for (int x = r - 1; x >= 0; x--) {
            cin >> str;
            if (str.find('#') != string::npos) {
                ma = max(ma, x);
                mi = min(mi, x);
            }
        }
        cout << ma - mi << endl;
    }

    return 0;
}