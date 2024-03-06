#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long n; cin >> n;

    long long ans = 0;
    int set = 0;
    for (int b = 60; b >= 0; b--) {
        if (n & (1LL << b)) {
            ans += b * (1LL << (b - 1));
            ans += set * (1LL << b);

            set++;
        }
    }
    ans += set;

    cout << ans << '\n';
}
