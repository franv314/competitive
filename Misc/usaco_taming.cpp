#include <bits/stdc++.h>
using namespace std;

#define INF 1000
#define MAXN 100

ifstream in("taming.in");
ofstream out("taming.out");

int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int main() {
    int N; in >> N;
    vector<int> log(N);
    for (auto &entry: log) {
        in >> entry;
    }
    
    for (int breakouts = 1; breakouts <= N; breakouts++) {
        for (int days_since_breakout = 1; days_since_breakout <= N; days_since_breakout++) {
            dp[N][breakouts][days_since_breakout] = INF;
        }
    }
    
    for (int day = N - 1; day >= 0; day--) {
        for (int breakouts = 0; breakouts <= N; breakouts++) {
            for (int days_since_breakout = 1; days_since_breakout <= N; days_since_breakout++) {
                int val = INF;
                if (breakouts > 0) val = min(val, dp[day + 1][breakouts - 1][1] + (log[day] != 0));
                val = min(val, dp[day + 1][breakouts][days_since_breakout + 1] + (log[day] != days_since_breakout));
                dp[day][breakouts][days_since_breakout] = val;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        out << (log[0] != 0) + dp[1][i - 1][1] << '\n';
    }
}