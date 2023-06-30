#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long u64;

#define MAXA 300
#define MAXB 301

int A, B;
long long K;
u64 dp[MAXB][MAXB][MAXA];

vector<int> get_powers() {
    vector<int> ret;
    int cur = 1;
    for (int _ = 0; _ <= B; _++) {
        ret.push_back(cur);
        cur = (cur * 10) % A;
    }
    return ret;
}

int main() {
    cin >> A >> B >> K;
    vector<int> powers = get_powers();

    dp[0][0][0] = 1;
    for (int cifre = 1; cifre <= B; cifre++) {
        for (int somma = 0; somma <= B; somma++) {
            for (int resto = 0; resto < A; resto++) {
                for (int next = 1; next <= 9; next++) {
                    int prev_somma, prev_resto;
                    if ((prev_somma = somma - next) < 0) continue;
                    prev_resto = (resto - (powers[cifre - 1] - A) * next) % A;
                    if (dp[cifre - 1][prev_somma][prev_resto])
                        dp[cifre][somma][resto] += dp[cifre - 1][prev_somma][prev_resto];
                }
            }
        }
    }

    int curr = 0;
    long long taken = 0;
    while (taken < K) {
        taken += dp[++curr][B][0];
    }
    taken -= dp[curr][B][0];

    int curr_somma = B, curr_resto = 0;

    while (curr) {
        int test = 0, next_somma, next_resto;
        while (taken < K) {
            test++;
            if ((next_somma = curr_somma - test) < 0) continue;
            next_resto = (curr_resto - (powers[curr - 1] - A) * test) % A;
            taken += dp[curr - 1][next_somma][next_resto];
        }
        cout << test;

        taken -= dp[curr - 1][next_somma][next_resto];
        curr_somma = next_somma, curr_resto = next_resto;
        curr--;
    }
}