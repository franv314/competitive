#include <bits/stdc++.h>
using namespace std;

constexpr int MAXV = 1000000;

struct Fenwick {
    vector<int> arr;

    void add(int p, int d) {
        for (; p < arr.size(); p += p & -p)
            arr[p] += d;
    }

    int query(int p) {
        int ans = 0;
        for (; p; p -= p & -p)
            ans += arr[p];
        return ans;
    }

    Fenwick(int N) : arr(N + 1) { }
};

vector<int> count(int N, vector<int> S, vector<int> P) {
    vector<int> ans(N);

    vector<array<int, 3>> mats(N);
    for (int i = 0; i < N; i++)
        mats[i] = {S[i], P[i], i};
        
    sort(mats.rbegin(), mats.rend());

    int dominators = 0;
    pair<int, int> cheapest = {1e9, 1e9};
    Fenwick fenwick(MAXV);
    for (auto [s, p, i]: mats) {
        int doms = fenwick.query(p);
        if (doms == 0) {
            dominators++;
            ans[i]--;
        }
        if (doms == 1) ans[cheapest.second]++;

        cheapest = min(cheapest, {p, i});
        fenwick.add(p, 1);
    }

    for (auto &x: ans) x += dominators;
    return ans;
}
