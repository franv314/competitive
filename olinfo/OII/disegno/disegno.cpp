#include <bits/stdc++.h>
#include "disegno.h"
using namespace std;

bool operator<(const Point &a, const Point &b) { return tie(a.x, a.y) < tie(b.x, b.y); }

vector<Point> draw(int N, int L, vector<Point> A, vector<Point> B) {
    map<Point, array<optional<Point>, 4>> adj;
    for (int i = 0; i < N; i++) {
        if (A[i].y == B[i].y) {
            adj[A[i]][1] = B[i];
            adj[B[i]][0] = A[i];
        } else {
            adj[A[i]][3] = B[i];
            adj[B[i]][2] = A[i];
        }
    }

    auto check_shape = [&](const Point &p) -> bool {
        auto [l, r, d, u] = adj[p];

        if (!l || !r || !d || !u) return false;

        auto [ll, rl, dl, ul] = adj[l.value()];
        if (!(ul && dl && rl && !ll) && l.value().x != 0) return false;

        auto [ld, rd, dd, ud] = adj[d.value()];
        if (!(ud && ld && rd && !dd) && d.value().y != 0) return false;

        auto [lu, ru, du, uu] = adj[u.value()];
        if (!(lu && ru && du) && u.value().y != L) return false;

        auto [lr, rr, dr, ur] = adj[r.value()];
        if (!(lr && dr && ur) && r.value().x != L) return false;

        return true;
    };

    queue<Point> q;
    set<Point> used;
    vector<Point> moves;

    for (auto &[point, _]: adj) {
        if (check_shape(point)) {
            q.push(point);
        }
    }

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (used.count(p)) continue;
        used.insert(p);

        moves.push_back(p);

        auto n = adj[p];

        if (n[0]) adj[n[0].value()][1] = {};
        if (n[1]) adj[n[1].value()][0] = {};
        if (n[2]) adj[n[2].value()][3] = {};
        if (n[3]) adj[n[3].value()][2] = {};
        adj.erase(p);

        vector<Point> maybe;

        for (auto point: n) {
            if (!point) continue;

            auto nn = adj[point.value()];

            if (nn[0] && nn[1] && !nn[2] && !nn[3]) {
                adj[nn[0].value()][1] = nn[1];
                adj[nn[1].value()][0] = nn[0];
                adj.erase(point.value());
            }
            if (!nn[0] && !nn[1] && nn[2] && nn[3]) {
                adj[nn[2].value()][3] = nn[3];
                adj[nn[3].value()][2] = nn[2];
                adj.erase(point.value());
            }
            if (!nn[0] && !nn[1] && !nn[2] && !nn[3]) {
                adj.erase(point.value());
            }

            if (nn[0]) maybe.push_back(nn[0].value());
            if (nn[1]) maybe.push_back(nn[1].value());
            if (nn[2]) maybe.push_back(nn[2].value());
            if (nn[3]) maybe.push_back(nn[3].value());
        }

        for (auto point: maybe) {
            if (check_shape(point)) q.push(point);
        }
    }

    if (!adj.empty()) return {};

    reverse(moves.begin(), moves.end());
    return moves;
}