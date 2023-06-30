#include <bits/stdc++.h>
using namespace std;

// input data
int N, K;
vector<long long> T;

long long dp[1001][1001];

int main() {
    //  uncomment the following lines if you want to read/write from files
    //  ifstream cin("input.txt");
    //  ofstream cout("output.txt");

    cin >> N >> K;
    T.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    for (int k = 1; k <= K; k++) {
        for (int n = 0; n < N; n++) {
            long long ma = INT64_MIN;
            for (int d1 = 2; d1 <= 12; d1++) {
                if (d1 != 2 && d1 != 12)
                    ma = max(ma, T[(n + d1) % N] + dp[(n + d1) % N][k - 1]);
                if (d1 & 1) 
                    continue;

                for (int d2 = 2; d2 <= 12; d2++) {
                    if (d2 != 2 && d2 != 12)
                        ma = max(ma, T[(n + d1) % N] + T[(n + d1 + d2) % N] + dp[(n + d1 + d2) % N][k - 1]);
                    if (d2 & 1)
                        continue;
                    for (int d3 = 2; d3 <= 12; d3++) {
                        ma = max(ma, T[(n + d1) % N] + T[(n + d1 + d2) % N] + T[(n + d1 + d2 + d3) % N] + dp[(n + d1 + d2 + d3) % N][k - 1]);
                    }
                }
            }
            dp[n][k] = ma;
        }
    }

    cout << dp[0][K] << endl;  // print the result
    return 0;
}