#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int* M, int* P) {
    vector<pair<int, int>> diff(N);
    for (int i = 0; i < N; i++)
        diff[i] = {i[M] - i[P], i};
    sort(diff.begin(), diff.end());
    long long ans = 0;
    for (int i = 0; i < N / 2; i++) {
        ans += P[diff[i].second];
    }
    for (int i = N / 2; i < N; i++) {
        ans += M[diff[i].second];
    }
    return ans;
}