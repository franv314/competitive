#include <bits/stdc++.h>
using namespace std;

#define MAXB 100'001

int sushi(int N, int B, vector<int> A) {
	bitset<MAXB> dp, new_dp;
    dp.set(0);

    int i = 0;
    for (;;) {
        if (i > 20) {
            return -1;
        }

        new_dp = dp;
        for (auto a: A) {
            new_dp |= new_dp << ((long long)a << i);
        }
        
        if (new_dp[B]) {
            i--;
            break;
        } else {
            i++;
            dp = new_dp;
        }
    }

    int ans = (1 << (i + 1)) - 1;
    for (; i >= 0; i--) {
        new_dp = dp;
        for (auto a: A) {
            new_dp |= new_dp << ((long long)a << i);
        }

        if (!new_dp[B]) {
            ans += (1 << i);
            dp = new_dp;
        }
    }

    return ans + 1;
}