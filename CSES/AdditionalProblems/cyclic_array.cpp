#include <bits/stdc++.h>
using namespace std;

#define LOG 18

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    long long k; cin >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<int>> lift(2 * n + 1, vector<int>(LOG));

    int r = 0;
    long long sum = 0;
    for (int l = 0; l < 2 * n; l++) {
        while (r < 2 * n && sum + a[r % n] <= k) {
            sum += a[r % n];
            r++;
        }
        
        lift[l][0] = r;
        sum -= a[l % n];
    }
    lift[2 * n][0] = 2 * n;

    for (int i = 2 * n; i >= 0; i--) {
        for (int j = 1; j < LOG; j++) {
            lift[i][j] = lift[lift[i][j - 1]][j - 1];
        }
    }

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        int pos = i;
        for (int j = LOG - 1; j >= 0; j--) {
            if (lift[pos][j] < i + n) {
                cnt += 1 << j;
                pos = lift[pos][j];
            }
        }

        ans = min(ans, cnt + 1);
    }

    cout << ans << '\n';
}