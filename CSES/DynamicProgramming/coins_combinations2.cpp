#include <bits/stdc++.h>
using namespace std;
 
#define MAXX 1'000'000
#define MAXN 100
 
int dp[MAXX + 1][MAXN];
 
constexpr int MOD = 1e9 + 7;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &c: a) cin >> c;

    fill(dp[0], dp[0] + MAXN, 1);
 
    for (int i = 1; i <= x; i++) {
        int *pd = dp[i];
        if (i >= a[0]) pd[0] = dp[i - a[0]][0];
        for (int j = 1; j < n; j++) {
            pd[j] = pd[j - 1];
            if (i >= a[j]) pd[j] = (pd[j] + dp[i - a[j]][j]) % MOD;
        }
    }
 
    cout << dp[x][n - 1] << '\n';
}