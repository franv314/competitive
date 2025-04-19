#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct Start {
    i64 c, s;
};

vector<i64> solve(int N, int X, vector<int> A, vector<i64> C, int Q, vector<i64> K) {
    vector<set<int>> pos_of(N);
    vector<i64> sum_of_ones(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        if (pos_of[A[i]].size() == 1)
            sum_of_ones[0] += i;
        pos_of[A[i]].insert(i);
    }

    for (int i = 1; i < 2 * N; i++) {
        sum_of_ones[i] = sum_of_ones[i - 1] + N - 1;
        int snd = *pos_of[A[i - 1]].begin() ^ *pos_of[A[i - 1]].rbegin() ^ (i - 1);
        
        if (snd < i)
            sum_of_ones[i] -= 2 * N - i + snd;
        else
            sum_of_ones[i] -= snd - i;
    }

    vector<pair<i64, int>> queries(Q);
    for (int i = 0; i < Q; i++)
        queries[i] = {K[i] + (i64)N * (N - 1) / 2, i};
    sort(queries.begin(), queries.end());
    vector<i64> ans(Q);

    vector<Start> starts(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        starts[i] = {C[i], sum_of_ones[i]};
    }
    sort(starts.begin(), starts.end(), [&](Start u, Start v) { return u.s < v.s; });

    multiset<i64> tops; tops.insert(2e18);
    for (auto [c, s]: starts) tops.insert(c);
    i64 bot = 2e18;
    int idx = 0;

    for (auto [k, i]: queries) {
        while (idx < 2 * N && starts[idx].s < k) {
            tops.erase(tops.find(starts[idx].c));
            bot = min(bot, starts[idx].c - X * starts[idx].s);
            idx++;
        }

        ans[i] = min(*tops.begin(), bot + X * k);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, X; cin >> N >> X;
    vector<int> A(2 * N);
    vector<i64> C(2 * N);
    for (auto &x: A) { cin >> x; x--; }
    for (auto &x: C) cin >> x;
    int Q; cin >> Q;
    vector<i64> K(Q);
    for (auto &x: K) cin >> x;

    vector<i64> ans = solve(N, X, std::move(A), std::move(C), Q, std::move(K));
    for (auto x: ans)
        cout << x << '\n';
}