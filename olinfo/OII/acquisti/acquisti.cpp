#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

struct Pair {
    int idx;
    long long size;
};

vector<long long> calcola(int T, int M, vector<long long> S, vector<long long> P) {
    vector<long long> R(M);
    vector<Pair> s(M);
    for (int i = 0; i < M; i++)
        s[i] = {i, P[i]};
    sort(s.begin(), s.end(), [&](Pair a, Pair b){
        return a.size < b.size;
    });

    int curr = 0;
    vector<Pair>::iterator valigia = s.begin(), e = s.end();
    long long sum = 0, count = 0;
    for (; valigia != e; valigia++) {
        while (sum + S[curr] * curr  <= valigia->size && curr < T) {
            sum += S[curr] * curr;
            count += S[curr];
            curr++;
        }
        if (curr + 1 > T) break;
        R[valigia->idx] = count + (valigia->size - sum) / curr;
    }
    for (; valigia != e; valigia++)
        R[valigia->idx] = count;
    return R;
}