#include <bits/stdc++.h>
using namespace std;

constexpr int BLOCK = 600;
typedef long long i64;

#define DIFF(x) ((x) >> 24)
#define PAR(x) ((x) & ((1 << 24) - 1))

struct DSU {
    vector<int> par;
    vector<pair<int*, int>> rollback;

    pair<int, bool> find(int node) {
        if (par[node] < 0) return {node, 0};
        auto [p, d] = find(PAR(par[node]));
        return {p, d ^ DIFF(par[node])};
    }

    bool join(int u, int v) {
        auto [tu, cu] = find(u);
        auto [tv, cv] = find(v);

        if (par[tu] > par[tv]) {
            swap(tu, tv);
        }

        if (tu == tv) return cu != cv;

        par[tu] += par[tv];
        par[tv] = tu | ((true ^ cu ^ cv) << 24);

        return true;
    }

    bool join_roll(int u, int v) {
        auto [tu, cu] = find(u);
        auto [tv, cv] = find(v);

        if (par[tu] > par[tv]) {
            swap(tu, tv);
        }

        if (tu == tv) return cu != cv;

        rollback.emplace_back(&par[tu], par[tu]);
        par[tu] += par[tv];

        rollback.emplace_back(&par[tv], par[tv]);
        par[tv] = tu | ((true ^ cu ^ cv) << 24);

        return true;
    }

    void roll() {
        while (!rollback.empty()) {
            auto [ptr, val] = rollback.back(); rollback.pop_back();
            *ptr = val;
        }
    }

    DSU(int n) : par(n, -1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
    }

    i64 ans = 0;
    int curr_dsu_start = 0;
    DSU dsu(N);

    auto build_from = [&](int l, int r) {
        dsu.par.assign(N, -1);
        for (int i = r; i >= l; i--) {
            if (!dsu.join(edges[i].first, edges[i].second))
                break;
            curr_dsu_start = i;
        }
    };

    for (int r = 0; r < M; r++) {
        if (!dsu.join(edges[r].first, edges[r].second)) {
            build_from(min(curr_dsu_start + BLOCK, r - 1), r);
        }

        int curr = min(curr_dsu_start, r);
        for (;;) {
            curr--;
            if (curr < 0 || !dsu.join_roll(edges[curr].first, edges[curr].second)) break;
        }
        dsu.roll();

        ans += r - curr;
    }

    cout << ans << '\n';
}