#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXK 200
#define MAXC 10000

int K, C, L;

bool nums[10000];
pair<int, int> dp[MAXC + 1][1000];

int main() {
    assert(2 == scanf("%d %d", &K, &C));
    for (int i = 0; i < K; i++) {
        assert(1 == scanf("%d", &L));
        nums[L] = true;
    }

    for (int pos = C - 1; pos; pos--) {
        for (int prev = 0; prev < 1000; prev++) {
            for (int i = 0; i < 10; i++) {
                int num = prev * 10 + i;
                int next = (prev % 100) * 10 + i;

                if (dp[pos][prev].first < dp[pos + 1][next].first + nums[num]) {
                    dp[pos][prev].first = dp[pos + 1][next].first + nums[num];
                    dp[pos][prev].second = i;
                }
            }
        }
    }

    int ma = INT_MIN, ma_idx;
    for (int start = 100; start < 1000; start++) {
        if (dp[3][start].first > ma) {
            ma = dp[3][start].first;
            ma_idx = start;
        }
    }

    printf("%d", ma_idx);
    for (int pos = 3; pos < C; pos++) {
        int next = dp[pos][ma_idx].second;
        printf("%d", next);

        ma_idx = (ma_idx % 100) * 10 + next;
    }
    putchar('\n');

    return 0;
}