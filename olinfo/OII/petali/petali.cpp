#include <bits/stdc++.h>
using namespace std;

int solve(int N, int S[]) {
    deque<int> divisors;
    for (int i = 1; i * i <= N; i++) {
        if (N % i) continue;
        divisors.push_back(i);
        if (i * i != N) divisors.push_back(N / i);
    }
    sort(divisors.rbegin(), divisors.rend());
    
    vector<int> next(N + 1);
    vector<vector<bool>> success(N + 1);
    
    for (auto d: divisors) {
        next[d] = INT_MAX;
        for (auto dd: divisors) {
            if (dd != d && dd % d == 0) {
                next[d] = min(next[d], dd);
            }
        }
    }
    
    long long ans = 0;
    divisors.pop_front();
    success[N].assign(N + 1, true);
    for (auto d: divisors) {
        success[d].resize(d + 1);
        for (int start = 0; start < d; start++) {
            bool can = true;
            for (int off = 0; off < next[d]; off += d) {
                if (S[start] != S[start + off] || !success[next[d]][start + off]) {
                    can = false;
                    break;
                }
            }
            //cout << d << " " << start << " " << can << endl;
            if (can) {
                success[d][start] = true;
                ans++;
            }
        }
    }
    return ans;
}