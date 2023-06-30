#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

map<int, int> days;

int organizza(int N, int X, int Y, vector<int> A, vector<int> B){
    for (int i = 0; i < N; i++) {
        days[A[i]]++;
        days[B[i] + 1]--;
    }
    int res = 0, curr = 0, rng_begin = 0;
    for (auto x: days) {
        if (Y >= rng_begin && X < x.first && N - curr > res) res = N - curr;
        curr += x.second;
        rng_begin = x.first;
    }
    if (Y >= rng_begin && N - curr > res) res = N - curr;
    return res;
}