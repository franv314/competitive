#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include "seats.h"
using namespace std;
    
typedef long long i64;
    
struct Info {
    i64 mi;
    int cnt;
};
    
void merge(const Info &a, const Info &b, Info &c) {
    if (a.mi < b.mi)
        c = a;
    else if (b.mi < a.mi)
        c = b;
    else
        c = {a.mi, a.cnt + b.cnt};
}

Info merge(const Info &a, const Info &b) {
    if (a.mi < b.mi)
        return a;
    if (b.mi < a.mi)
        return b;
    return {a.mi, a.cnt + b.cnt};
}

class SegTree {
    vector<Info> arr;
    vector<i64> lazy;
    int s;
    
    void push(int n, int nb, int ne) {
        if (!lazy[n]) return;
    
        arr[n].mi += lazy[n];
        if (nb + 1 != ne) {
            lazy[2 * n] += lazy[n];
            lazy[2 * n + 1] += lazy[n];
        }
    
        lazy[n] = 0;
    }
    
    void update(int l, int r, i64 d, int n, int nb, int ne) {
        push(n, nb, ne);
        if (ne <= l || nb >= r) return;
        if (l <= nb && ne <= r) {
            lazy[n] = d;
            push(n, nb, ne);
            return;
        }
    
        update(l, r, d, 2 * n, nb, (nb + ne) / 2);
        update(l, r, d, 2 * n + 1, (nb + ne) / 2, ne);
    
        merge(arr[2 * n], arr[2 * n + 1], arr[n]);
    }
    
    Info query(int l, int r, int n, int nb, int ne) {
        push(n, nb, ne);
        if (ne <= l || nb >= r) return {(i64)1e18, 1};
        if (l <= nb && ne <= r) return arr[n];
    
        return merge(
            query(l, r, 2 * n, nb, (nb + ne) / 2),
            query(l, r, 2 * n + 1, (nb + ne) / 2, ne));
    }
    
public:
    
    void update(int l, int r, i64 d) { update(l, r, d, 1, 0, s); }
    int query(int l, int r) { return query(l, r, 1, 0, s).cnt; }
    
    SegTree() { }
    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s, {0, 1});
        lazy.resize(2 * s);
    
        for (int i = s - 1; i > 0; i--)
            merge(arr[2 * i], arr[2 * i + 1], arr[i]);
    }
};
    
#define GOOD_SQUARE_VALUE 1
#define BAD_SQUARE_VALUE ((int)1e7)
    
int H, W;
vector<vector<int>> grid;
vector<pair<int, int>> pos;
    
SegTree segtree;
    
bool get_status(int i, int j, int t) {
    if (i < 0 || j < 0 || i >= H || j >= W)
        return false;
    return grid[i][j] <= t;
}
    
int get_square_value(int x, int y, int dx, int dy, int t) {
    int cnt = get_status(x, y, t) + get_status(x + dx, y, t)
            + get_status(x, y + dy, t) + get_status(x + dx, y + dy, t);
    
    switch (cnt) {
    case 1: return GOOD_SQUARE_VALUE;
    case 3: return BAD_SQUARE_VALUE;
    default: return 0;
    }
}
    
void do_update(int idx, bool rev = false) {
    auto [x, y] = pos[idx];
    
    int factor = rev ? -1 : +1;
    i64 upd = 0;
    
    // Remove old squares
    for (auto dx: {-1, +1})
        for (auto dy: {-1, +1})
            upd -= get_square_value(x, y, dx, dy, idx - 1) * factor;
    
    // Add new squares
    for (auto dx: {-1, +1})
        for (auto dy: {-1, +1})
            upd += get_square_value(x, y, dx, dy, idx) * factor;
    
    // Push to segment
    segtree.update(idx, H * W, upd);
}
    
void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
    ::H = H, ::W = W;
    grid.assign(H, vector<int>(W));
    pos.resize(H * W);
    
    for (int i = 0; i < H * W; i++) {
        pos[i] = {R[i], C[i]};
        grid[R[i]][C[i]] = i;
    }
    
    segtree = SegTree(H * W);
    
    for (int i = 0; i < H * W; i++) {
        do_update(i);
    }
}
    
int swap_seats(int a, int b) {
    set<pair<int, int>> to_update;
    
    for (auto c: {a, b})
        for (int x = max(0, pos[c].first - 1); x <= min(H - 1, pos[c].first + 1); x++)
            for (int y = max(0, pos[c].second - 1); y <= min(W - 1, pos[c].second + 1); y++)
                to_update.emplace(x, y);
    
    for (auto [x, y]: to_update)
        do_update(grid[x][y], true);
    
    swap(pos[a], pos[b]);
    grid[pos[a].first][pos[a].second] = a;
    grid[pos[b].first][pos[b].second] = b;
    
    for (auto [x, y]: to_update)
        do_update(grid[x][y]);
    
    return segtree.query(0, H * W);
}