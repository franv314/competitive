#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    vector<int> lazy;
    int s;

    void push(int n, int nb, int ne) {
        if (lazy[n]) {
            arr[n] += lazy[n];

            if (nb + 1 != ne) {
                lazy[2 * n] += lazy[n];
                lazy[2 * n + 1] += lazy[n];
            }

            lazy[n] = 0;
        }
    }

    void update(int l, int r, int d, int n, int nb, int ne) {
        push(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            lazy[n] += d;
            push(n, nb, ne);
            return;
        }

        update(l, r, d, 2 * n, nb, (nb + ne) / 2);
        update(l, r, d, 2 * n + 1, (nb + ne) / 2, ne);
        arr[n] = max(arr[2 * n], arr[2 * n + 1]);
    }

    int query(int x, int n, int nb, int ne, int acc = 0) {
        acc += lazy[n];
        if (arr[n] + acc < x) return 2e9;
        if (nb + 1 == ne) return nb;

        int v = query(x, 2 * n, nb, (nb + ne) / 2, acc);
        if (v != 2e9) return v;
        return query(x, 2 * n + 1, (nb + ne) / 2, ne, acc);
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
        lazy.resize(2 * s);
    };
};

vector<pair<int, int>> flags;
int F, S;

optional<pair<int, int>> check(int r) {
    vector<int> ys;
    vector<array<int, 4>> upd;

    ys.reserve(3 * flags.size());
    upd.reserve(6 * flags.size());

    for (auto &[x, y]: flags) {
        ys.push_back(y - r);
        ys.push_back(y);
        ys.push_back(y + r);

        upd.push_back({x - r, y, y, +1});
        upd.push_back({x, y, y, -1});
        upd.push_back({x + 1, y, y, +1});
        upd.push_back({x + r + 1, y, y, -1});

        upd.push_back({x, y - r, y + r, +1});
        upd.push_back({x + 1, y - r, y + r, -1});
    }

    if (F >= 4 * r + 1) return {{0, 0}};

    for (auto &y: ys) y = clamp(y, 0, S - 1);
    for (auto &[x, yl, yr, d]: upd) {
        x = clamp(x, 0, S - 1);
    }

    sort(ys.begin(), ys.end());
    ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
    ys.back() = 2e9;

    sort(upd.begin(), upd.end());
    SegTree segtree(ys.size());

    for (int i = 0; i < upd.size(); i++) {
        auto &[x, yl, yr, d] = upd[i];
        
        int ysl = lower_bound(ys.begin(), ys.end(), yl) - ys.begin();
        int ysr = lower_bound(ys.begin(), ys.end(), yr) - ys.begin();

        segtree.update(ysl, ysr + 1, d, 1, 0, segtree.s);

        if (i == upd.size() - 1 || x != upd[i + 1][0]) {
            int smallest_good_y = segtree.query(4 * r + 1 - F, 1, 0, segtree.s);
            if (smallest_good_y != 2e9) {
                return {{x, ys[smallest_good_y]}};
            }
        }
    }

    return {};
}

array<int, 3> find_plus(int N, int S, int F, vector<int> y, vector<int> x){
    ::F = F, ::S = S;
    for (int i = 0; i < N; i++) {
        flags.emplace_back(y[i], x[i]);
    }

    pair<int, int> ans;
    int l = max(0, (F - 1) / 4), r = (F + N - 1) / 4 + 1;

    while (l + 1 < r) {
        int m = (l + r) / 2;

        optional<pair<int, int>> x = check(m);
        if (x) {
            ans = x.value();
            l = m;
        } else {
            r = m;
        }
    }

    return {l, ans.first, ans.second};
}