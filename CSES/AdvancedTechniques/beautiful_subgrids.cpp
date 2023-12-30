#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#define MAXN 3'000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<bitset<MAXN>> grid(n);
    for (auto &x: grid) {
        cin >> x;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int cnt = (grid[i] & grid[j]).count();
            ans += cnt * (cnt - 1) >> 1;
        }
    }

    cout << ans << '\n';
}