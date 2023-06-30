#include <bits/stdc++.h>
using namespace std;

int zero(int N, vector<int> B) {
    long long sum = 0;
    for (int i = 0; i < N - 1; i++) {
        sum += B[i];
        if (sum == 0) {
            return 2;
        }
    }
    return -1;
}

int pos(int N, vector<int> B, long long tot) {
    long long sum = 0;
    vector<long long> tests = {};
    for (auto x: B) {
        sum += x;
        if (sum > 0 && sum < tot && tot % sum == 0) {
            tests.push_back(sum);
        }
    }
    for (auto it = tests.rbegin(); it != tests.rend(); it++) {
        long long frac = *it;
        long long sum = 0, count = 0;
        for (auto x: B) {
            sum += x;
            if (sum == frac) {
                sum = 0;
                count++;
            }
        }
        if (count == tot / frac) return count;
    }
    return -1;
}

int taglia(int N, vector<int> B) {
    long long sum = accumulate(B.begin(), B.end(), 0LL);
    if (sum == 0) return zero(N, B);
    if (sum < 0)
        for (auto &x: B)
            x *= -1;
    return pos(N, B, abs(sum));
}