#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int solve(long long N) {
    array<int, 3> ans = {1, 0, 0};
    array<int, 3> base = {0, 1, 1};

    for (; N; N >>= 1) {
        if (N & 1) {
            array<int, 3> old_ans = ans;
            ans = {0, 0, 0};
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ans[(i + j) % 3] = (ans[(i + j) % 3] + (long long)old_ans[i] * base[j]) % MOD;
                }
            }
        }

        array<int, 3> old_base = base;
        base = {0, 0, 0};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                base[(i + j) % 3] = (base[(i + j) % 3] + (long long)old_base[i] * old_base[j]) % MOD;
            }
        }
    }

    return ans[0];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
        long long N; cin >> N;
        cout << solve(N) << '\n';
    }
}