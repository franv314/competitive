#include "nile.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct CC {
    i64 sum;
    int best_even, best_odd, best;
    int par, size, l, r;

    void skip(int diff) { best = min(best, diff); }

    i64 get_best() const { return min({best, l & 1 ? best_odd : best_even}); }
    i64 get_cost() const { return sum + (size & 1) * get_best(); }
};

struct DSU {
    vector<CC> arr;
    vector<int> A, B;
    i64 cost;

    int find(int u) {
        if (arr[u].par == u) return u;
        return arr[u].par = find(arr[u].par);
    }

    void join(int i) {
        int u = find(i);
        int v = find(i + 1);
        
        if (u == v) return;
        if (arr[u].size < arr[v].size) swap(u, v);

        cost -= arr[u].get_cost();
        cost -= arr[v].get_cost();

        arr[u].size += arr[v].size;
        arr[u].r = max(arr[u].r, arr[v].r);
        arr[u].l = min(arr[u].l, arr[v].l);
        arr[v].par = u;

        arr[u].sum += arr[v].sum;
        arr[u].best = min(arr[u].best, arr[v].best);
        arr[u].best_even = min(arr[u].best_even, arr[v].best_even);
        arr[u].best_odd = min(arr[u].best_odd, arr[v].best_odd);

        cost += arr[u].get_cost();
    }

    void skip(int i) {
        int u = find(i);

        cost -= arr[u].get_cost();
        arr[u].skip(A[i] - B[i]);
        cost += arr[u].get_cost();
    }

    DSU(int N, const vector<int> &A, const vector<int> &B) : arr(N), A(A), B(B), cost(0) {
        for (int i = 0; i < N; i++) {
            arr[i] = {B[i], i & 1 ? (int)2e9 : A[i] - B[i], i & 1 ? A[i] - B[i] : (int)2e9, (int)2e9, i, 1, i, i};
            cost += arr[i].get_cost();
        }
    }
};

enum EventType { JOIN, SKIP, QUERY };
struct Event {
    EventType type;
    int time, position;
};

bool operator<(const Event &a, const Event &b) { return tie(a.time, a.type) < tie(b.time, b.type); }

vector<long long> calculate_costs(vector<int> W, vector<int> A, vector<int> B, vector<int> E) {
    const int N = W.size();
    const int Q = E.size();

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int u, int v) { return W[u] < W[v]; });
    sort(W.begin(), W.end());

    vector<int> sA(N), sB(N);

    for (int i = 0; i < N; i++) {
        sA[i] = A[order[i]];
        sB[i] = B[order[i]];
    }

    vector<Event> events;
    for (int i = 0; i < Q; i++)
        events.push_back({QUERY, E[i], i});
    for (int i = 0; i < N - 1; i++)
        events.push_back({JOIN, W[i + 1] - W[i], i});
    for (int i = 1; i < N - 1; i++)
        events.push_back({SKIP, W[i + 1] - W[i - 1], i});
    
    DSU dsu(N, sA, sB);
    vector<i64> ans(E.size());
    sort(events.begin(), events.end());

    for (auto [type, _, idx]: events) {
        switch (type) {
        case JOIN:
            dsu.join(idx);
            break;
        case SKIP:
            dsu.skip(idx);
            break;
        case QUERY:
            ans[idx] = dsu.cost;
            break;
        }
    }

    return ans;
}
