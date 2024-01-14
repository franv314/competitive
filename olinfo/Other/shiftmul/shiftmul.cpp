#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int b, int e) {
    int ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    }
    return ans;
}

vector<int> execute(int N, int K, int D, vector<int> A) {
    vector<vector<int>> cycles;
    vector<pair<int, int>> visited(N, {-1, -1});

    for (int i = 0; i < N; i++) {
        if (visited[i].first != -1) continue;

        cycles.emplace_back();
        for (int curr = i; visited[curr].first == -1; curr = (curr - D + N) % N) {
            cycles.back().push_back(curr);
            visited[curr] = {cycles.size() - 1, cycles.back().size() - 1};
        }
    }

    vector<vector<int>> pp(cycles.size());
    for (int i = 0; i < cycles.size(); i++) {
        pp[i].assign(cycles[i].size() + 1, 1);
        for (int j = 1; j < pp[i].size(); j++) {
            pp[i][j] = (long long)pp[i][j - 1] * A[cycles[i][j - 1]] % MOD;
        }
    }

    vector<int> ans(N);
    for (int i = 0; i < N; i++) {
        auto [c, p] = visited[i];

        int complete_cycles = K / cycles[c].size();
        int extra_things = K % cycles[c].size();

        int l = p;
        int r = (l + extra_things) % cycles[c].size();

        int extra_prod = (long long)pp[c][max(l, r)] * fexp(pp[c][min(l, r)], MOD - 2) % MOD;
        if (l > r) {
            extra_prod = (long long)pp[c].back() * fexp(extra_prod, MOD - 2) % MOD;
        }

        int cycle_prod = fexp(pp[c].back(), complete_cycles);

        ans[i] = (long long)cycle_prod * extra_prod % MOD;
    }

    return ans;
}