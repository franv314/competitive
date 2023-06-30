#include <bits/stdc++.h>
using namespace std;

#define MAXM 1'000'000'000

const long long INF = 1e16;

class SegTree {
    int size;
    long long *min_tree;
    pair<long long, bool> *lazy;

    void update(int N, int NB, int NE) {
        if (lazy[N].second) {
            min_tree[N] = lazy[N].first;
            if (NB + 1 != NE)
                lazy[2 * N] = lazy[2 * N + 1] = lazy[N];
            lazy[N] = {0, false};
            return;
        }
        if (lazy[N].first) {
            min_tree[N] += lazy[N].first;
            if (NB + 1 != NE) {
                lazy[2 * N].first += lazy[N].first;
                lazy[2 * N + 1].first += lazy[N].first;
            }
            lazy[N] = {0, false};
            return;
        }
    }

    void add(int L, int R, long long diff, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return; // OUTSIDE
        if (L <= NB && NE <= R) { // FULLY CONTAINED
            min_tree[N] += diff;
            if (NB + 1 != NE) {
                lazy[2 * N].first += diff;
                lazy[2 * N + 1].first += diff;
            }
            return;
        }
        if (NB + 1 == NE) {
            min_tree[N] += diff;
        } else {
            add(L, R, diff, 2 * N, NB, (NB + NE) / 2);
            add(L, R, diff, 2 * N + 1, (NB + NE) / 2, NE);
            min_tree[N] = min(min_tree[2 * N], min_tree[2 * N + 1]);
        }
    }

    void set_range(int L, int R, long long val, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return; // OUTSIDE
        if (L <= NB && NE <= R) { // FULLY CONTAINED
            min_tree[N] = val;
            if (NB + 1 != NE)
                lazy[2 * N] = lazy[2 * N + 1] = {val, true};
            return;
        }
        if (NB + 1 == NE) {
            min_tree[N] = val;
        } else {
            set_range(L, R, val, 2 * N, NB, (NB + NE) / 2);
            set_range(L, R, val, 2 * N + 1, (NB + NE) / 2, NE);
            min_tree[N] = min(min_tree[2 * N], min_tree[2 * N + 1]);
        }
    }

    long long get_min(int L, int R, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return 1e18; // OUTSIDE
        if (L <= NB && NE <= R) // FULLY CONTAINED
            return min_tree[N];
        return min(
            get_min(L, R, 2 * N, NB, (NB + NE) / 2),
            get_min(L, R, 2 * N + 1, (NB + NE) / 2, NE)
        );
    }

public:

    void set_range(int L, int R, long long val) {
        set_range(L, R, val, 1, 0, size / 2);
    }

    void add(int L, int R, long long diff) {
        add(L, R, diff, 1, 0, size / 2);
    }

    long long get_min(int L, int R) {
        return get_min(L, R, 1, 0, size / 2);
    }

    SegTree(int N) {
        size = 2 << (int) ceil(log2(N));
        min_tree = (long long*) calloc(size, sizeof(long long));
        lazy = (pair<long long, bool>*) calloc(size, sizeof(pair<long long, bool>));
    }
} taken(500'005);

pair<int, int> solve(pair<int, int> jerry, vector<pair<int, int>> cats, int M) {
    auto [rj, cj] = jerry;
    int escape_time = INT_MAX;

    // Escape to the top
    {
        long long l = -INF, r = INF;
        for (auto [rc, cc]: cats) {
            if (cc > cj) continue;
            if (rc >= rj) r = min(r, (long long)rc);
            if (rc <= rj) l = max(l, (long long)rc);
        }
        if ((r - l) / 2 > cj - 1) escape_time = min(escape_time, cj - 1);
    }
    // Escape to the bottom
    {
        long long l = -INF, r = INF;
        for (auto [rc, cc]: cats) {
            if (cc < cj) continue;
            if (rc >= rj) r = min(r, (long long)rc);
            if (rc <= rj) l = max(l, (long long)rc);
        }
        if ((r - l) / 2 > M - cj) escape_time = min(escape_time, M - cj);
    }
    // Escape to the left
    {
        long long l = -INF, r = INF;
        for (auto [rc, cc]: cats) {
            if (rc > rj) continue;
            if (cc >= cj) r = min(r, (long long)cc);
            if (cc <= cj) l = max(l, (long long)cc);
        }
        if ((r - l) / 2 > rj - 1) escape_time = min(escape_time, rj - 1);
    }
    // Escape to the right
    {
        long long l = -INF, r = INF;
        for (auto [rc, cc]: cats) {
            if (rc < rj) continue;
            if (cc >= cj) r = min(r, (long long)cc);
            if (cc <= cj) l = max(l, (long long)cc);
        }
        if ((r - l) / 2 > M - rj) escape_time = min(escape_time, M - rj);
    }

    
    if (escape_time != INT_MAX) return { true, escape_time };

    for (auto [rc, cc]: cats) {
        if (rc == rj && cc == cj) {
            return { false, 0 };
        }
    }

    int l = 0, r = M + 1;

    while (l + 1 < r) {
        int m = (l + r) / 2;

        int L = max(rj - m, 1),
            R = min(rj + m, M),
            T = max(cj - m, 1),
            B = min(cj + m, M);

        map<int, int> pos;
        pos[T], pos[B];
        for (auto [rc, cc]: cats) {
            if (!(rc - m > R || rc + m < L)) {
                pos[max(cc - m, T)];
                pos[min(cc + m, B)];
                pos[max(cc - m, T) + 1];
                pos[min(cc + m, B) + 1];
                pos[max(cc - m, T) - 1];
                pos[min(cc + m, B) - 1];
            }
        }

        int p = 0;
        for (auto &[_, v]: pos) {
            v = p++;
        }

        map<int, pair<vector<pair<int, int>>, vector<pair<int, int>>>> ranges;
        ranges[L], ranges[R];
        for (auto [rc, cc]: cats) {
            if (!(rc - m > R || rc + m < L)) {
                ranges[max(rc - m, L)].second.push_back({pos[max(cc - m, T)], pos[min(cc + m, B)]});
                if (rc + m < R)
                    ranges[rc + m + 1].first.push_back({pos[max(cc - m, T)], pos[min(cc + m, B)]});
            }
        }

        taken.set_range(0, p, 0);
        for (auto [row, rngs]: ranges) {
            for (auto [t, b]: rngs.first)
                taken.add(t, b + 1, -1);
            for (auto [t, b]: rngs.second)
                taken.add(t, b + 1, +1);

            if (taken.get_min(pos[T], pos[B] + 1) == 0) {
                l = m;
                goto escaped;
            }
        }

        r = m;
        escaped:;
    }
    return { false, l + 1 };
}

int main() {
    int M, T; cin >> M >> T;
    while (T--) {
        pair<int, int> jerry; cin >> jerry.first >> jerry.second;
        int N; cin >> N;
        vector<pair<int, int>> cats(N);
        for (auto &[r, c]: cats) cin >> r >> c;

        auto [escapes, time] = solve(jerry, cats, M);
        cout << (escapes ? "ESCAPED " : "CAUGHT ") << time << "\n";
    }
}