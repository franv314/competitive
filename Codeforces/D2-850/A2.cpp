#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int aw = 1, ab = 0, bw = 0, bb = 0, taken = 1;
        n--;

        for (int d = 2; n; d++) {
            if (d & 2) {
                if (taken & 1) {
                    bw += min(d, n) / 2;
                    bb += (min(d, n) + 1) / 2;
                } else {
                    bb += min(d, n) / 2;
                    bw += (min(d, n) + 1) / 2;
                }
            } else {
                if (taken & 1) {
                    aw += min(d, n) / 2;
                    ab += (min(d, n) + 1) / 2;
                } else {
                    ab += min(d, n) / 2;
                    aw += (min(d, n) + 1) / 2;
                }
            }
            taken += min(d, n);
            n -= min(d, n);
        }
        cout << aw << " " << ab << " " << bw << " " << bb << "\n";
    }
}