#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    vector<int> dp(5'001);

    for (int i = 1; i < 5'001; i++) {
        vector<bool> free(8192, 1);
        for (int j = 1; j < (i + 1) / 2; j++) {
            free[dp[j] ^ dp[i - j]] = false;
        }

        for (int j = 0; j < 8192; j++) {
            if (free[j]) {
                dp[i] = j;
                break;
            }
        }
    }

    while (t--) {
        int n; cin >> n;
        if (n > 5000 || dp[n]) cout << "first\n";
        else cout << "second\n";
    }
}