#include <bits/stdc++.h>
using namespace std;

struct FenwickTree {
    vector<long long> sum;
    vector<int> cnt;

    void add(int pos, long long val) {
        for (; pos < sum.size(); pos += pos & -pos) {
            sum[pos] += val;
            cnt[pos]++;
        }
    }

    void remove(int pos, long long val) {
        for (; pos < sum.size(); pos += pos & -pos) {
            sum[pos] -= val;
            cnt[pos]--;
        }
    }

    pair<long long, int> binsearch(long long k) {
        long long acc_sum = 0;
        int acc_cnt = 0;
        int pos = 0;
        for (int b = 20; b >= 0; b--) {
            int j = 1 << b;
            if (pos + j >= sum.size() || acc_sum + sum[pos + j] > k) continue;

            acc_sum += sum[pos + j];
            acc_cnt += cnt[pos + j];
            pos += j;
        }

        return {acc_sum, acc_cnt};
    }

    FenwickTree(int n) : sum(n + 1), cnt(n + 1) { }
};

long long bfs(int N, long long K, vector<int> P, vector<int> F) {
    vector<pair<int, int>> events;
    events.reserve(2 * N);
    for (int i = 0; i < N; i++) {
        if (F[i] > P[i]) continue;
        events.emplace_back(2 * F[i], 2 * i);
        events.emplace_back(2 * P[i] + 1, 2 * i + 1);
    }

    sort(events.begin(), events.end());

    vector<pair<int, int>> F_copy(N);
    for (int i = 0; i < N; i++) {
        F_copy[i] = {F[i], i};
    }

    sort(F_copy.begin(), F_copy.end());
    vector<int> compress(N);

    for (int i = 0; i < N; i++) {
        compress[F_copy[i].second] = i + 1;
    }

    FenwickTree fenwick(N);

    long long ma = 0;

    for (auto [_, i]: events) {
        if (!(i & 1)) {
            i >>= 1;
            fenwick.add(compress[i], F[i]);
        } else {
            i >>= 1;

            long long cost = P[i];
            auto [price, people] = fenwick.binsearch(K);
            ma = max(ma, people * cost - price);

            fenwick.remove(compress[i], F[i]);
        }
        
    }

    return ma;
}
