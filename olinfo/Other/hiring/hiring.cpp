#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<pair<int, long long>> arr;
    int s;

    void add(int p, int v) {
        arr[p += s] = {1, v};
        for (p >>= 1; p; p >>= 1)
            arr[p] = {arr[2 * p].first + arr[2 * p + 1].first, arr[2 * p].second + arr[2 * p + 1].second};
    }

    pair<int, int> query(long long budget) {
        int cnt = 0;
        long long spent = 0;
        for (int curr = 1; curr < s;) {
            if (spent + arr[2 * curr].second <= budget) {
                cnt += arr[2 * curr].first;
                spent += arr[2 * curr].second;
                curr = 2 * curr + 1;
            } else {
                curr = 2 * curr;
            }
        }
        return {cnt, spent};
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N; in >> N;
    long long B; in >> B;

    vector<int> S(N), Q(N);
    for (int i = 0; i < N; i++)
        in >> S[i] >> Q[i];

    vector<int> workers(N);
    iota(workers.begin(), workers.end(), 0);
    sort(workers.begin(), workers.end(), [&](int a, int b) {
        return S[a] * Q[b] < S[b] * Q[a];
    });

    vector<int> workers_by_q(N);
    iota(workers_by_q.begin(), workers_by_q.end(), 0);
    sort(workers_by_q.begin(), workers_by_q.end(), [&](int a, int b) {
        return Q[a] < Q[b];
    });
    vector<int> pos_of(N);
    for (int i = 0; i < N; i++)
        pos_of[workers_by_q[i]] = i;
    
    SegTree segtree(N);
    tuple<int, long long, int, int> best = {-1, -1, -1, -1};

    for (auto i: workers) {
        segtree.add(pos_of[i], Q[i]);
        long long budget = B * Q[i] / S[i];
        auto [cnt, spent] = segtree.query(budget);

        if (cnt > get<0>(best)) {
            best = {cnt, (long long)spent * S[i], Q[i], i};
        } else if (cnt == get<0>(best) && (__int128_t)spent * S[i] * get<2>(best) < (__int128_t)get<1>(best) * Q[i]) {
            best = {cnt, (long long)spent * S[i], Q[i], i};
        }
    }

    auto [cnt, _, __, j] = best;
    
    out << cnt << endl;
    for (auto i: workers_by_q) {
        if (S[i] * Q[j] <= S[j] * Q[i] && cnt) {
            cnt--;
            out << i + 1 << '\n';
        }
    }
}