#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int ma = INT_MIN, mi = INT_MAX, mi_am = 0, ma_am = 0;
        while (n--) {
            int temp; cin >> temp;
            if (temp == ma) ma_am++;
            else if (temp > ma) ma = temp, ma_am = 1;

            if (temp == mi) mi_am++;
            else if (temp < mi) mi = temp, mi_am = 1;
        }
        if (ma == mi) cout << mi_am * (long long)(mi_am - 1) << endl;
        else cout << 2 * mi_am * (long long)ma_am << endl;
    }

    return 0;
}