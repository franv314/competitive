#include <bits/stdc++.h>
using namespace std;

typedef long double f80;

struct Point {
    f80 x, y;
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
    f80 operator^(const Point &o) const { return x * o.y - y * o.x; }
};

partial_ordering orient(const Point &o, const Point &p, const Point &q) {
    return ((p - o) ^ (q - o)) <=> 0;
}

vector<optional<f80>> solve(int N, int Q, vector<int> A, vector<int> B, vector<int> C, vector<int> D) {
    vector<Point> points(N);
    for (int i = 0; i < N; i++) {
        points[i] = {(f80)A[i] / B[i], (f80)1 / B[i]};
    }

    sort(points.begin(), points.end(), [&](const Point &p, const Point &q) {
        return tie(p.x, p.y) < tie(q.x, q.y); 
    });

    vector<Point> hull;
    for (auto pt: points) {
        while (hull.size() > 1 && orient(hull[hull.size() - 2], hull[hull.size() - 1], pt) <= 0)
            hull.pop_back();
        hull.push_back(pt);
    }

    while (hull.size() > 1 && hull[hull.size() - 2].y <= hull[hull.size() - 1].y)
        hull.pop_back();
    
    vector<optional<f80>> ans(Q);
    for (int i = 0; i < Q; i++) {
        f80 lim = (f80)C[i] / D[i];

        auto it = upper_bound(hull.begin(), hull.end(), lim, [&](f80 lim, const Point &p) {
            return p.x > lim;
        });

        if (it == hull.begin())
            continue;

        f80 rhythm;
        if (it == hull.end()) {
            rhythm = prev(it)->y;
        } else {
            auto [x0, y0] = *prev(it);
            auto [x1, y1] = *it;

            rhythm = (y1 - y0) / (x1 - x0) * (lim - x0) + y0;
        }

        ans[i] = rhythm * D[i];
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
        cin >> A[i] >> B[i];

    int Q; cin >> Q;
    vector<int> C(Q), D(Q);
    for (int i = 0; i < Q; i++)
        cin >> C[i] >> D[i];

    vector<optional<f80>> ans = solve(N, Q, std::move(A), std::move(B), std::move(C), std::move(D));

    cout << fixed << setprecision(15);
    for (auto x: ans) {
        if (x)
            cout << x.value() << '\n';
        else
            cout << "-1\n";
    }
}