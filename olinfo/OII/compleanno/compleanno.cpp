#include <bits/stdc++.h>
using namespace std;

void aggiungi();
void copia();
void incolla();

const int mul[] = {2, 3, 4, 5, 7, 11, 13, 17, 19};
unordered_map<long long, pair<int, int>> dp;

void rec(long long N) {
    pair<int, int> mi = {INT_MAX, -1};
    for (auto k: mul) {
        int adds = N % k;
        long long rec_on = N / k;
        if (!dp.count(rec_on)) rec(rec_on);
        
        mi = min(mi, {k + 1 + adds + dp[rec_on].first, k});
    }
    dp[N] = mi;
}

void solve(long long N) {
    int move = dp[N].second;
    if (move == 1) {
        solve(N - 1);
        aggiungi();
    } else if (move != 0) {
        solve(N / move);
        
        copia();
        for (int _ = 1; _ < move; _++) incolla();
        for (int _ = 0; _ < N % move; _++) aggiungi();
    }
}

void auguri(long long N) {
    dp[0] = {0, 0};
    for (int i = 1; i < 5; i++) dp[i] = {i, 1}; 
	
	if (!dp.count(N)) rec(N);
	solve(N);
}