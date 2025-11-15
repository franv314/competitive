#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N, S; cin >> N >> S;
    vector<int> H(N);
    for (auto &x: H) cin >> x;

    vector<vector<int>> dp_pref(N + 1, vector<int>(S + 1));
    vector<vector<int>> dp_suff(N + 1, vector<int>(S + 1));

    dp_pref[0][0] = true;
    for (int i = 1; i <= N; i++) {
        dp_pref[i] = dp_pref[i - 1];
        for (int k = H[i - 1]; k <= S; k++)
            dp_pref[i][k] |= dp_pref[i - 1][k - H[i - 1]];
    }
        
    dp_suff[N][0] = true;
    for (int i = N - 1; i >= 0; i--) {
        dp_suff[i] = dp_suff[i + 1];
        for (int k = H[i]; k <= S; k++)
            dp_suff[i][k] |= dp_suff[i + 1][k - H[i]];
    }

    for (int i = 0; i < N; i++) {
        bool ok = false;
        for (int l = 0; l <= S; l++) {
            ok |= dp_pref[i][l] && dp_suff[i + 1][S - l];
        }
        cout << (ok ? "NO\n" : "YES\n");
    }
}