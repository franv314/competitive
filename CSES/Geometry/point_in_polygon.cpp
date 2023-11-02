#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;

    Point() {}
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    __int128_t operator^(const Point &other) const { return (__int128_t)x * other.y - (__int128_t)y * other.x; }
};

int orient(const Point &o, const Point &p, const Point &q) {
    __int128_t cross = (p - o) ^ (q - o);
    if (cross == 0) return 0;
    if (cross > 0) return 1;
    return -1;
}

strong_ordering operator<=>(const Point &a, const Point &b) { return tie(a.x, a.y) <=> tie(b.x, b.y); }

bool intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
    int or_1 = orient(p1, p2, p3);
    int or_2 = orient(p1, p2, p4);
    int or_3 = orient(p3, p4, p1);
    int or_4 = orient(p3, p4, p2);

    if (!or_1 && !or_2 && !or_3 && !or_4) {
        if (p1 < p3 && p2 < p3 && p1 < p4 && p2 < p4) {
            return false;
        }
        if (p1 > p3 && p2 > p3 && p1 > p4 && p2 > p4) {
            return false;
        }
        return true;
    } else {
        return or_1 != or_2 && or_3 != or_4;
    }
}

bool on_line(const Point &p1, const Point &p2, const Point &p3) {
    return ((p1 <= p3 && p3 <= p2) || (p1 >= p3 && p3 >= p2)) && orient(p1, p2, p3) == 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<Point> poly(n);
    for (auto &p: poly) {
        cin >> p.x >> p.y;
        p.x *= 2;
        p.y *= 2;
    }

    while (m--) {
        Point p; cin >> p.x >> p.y;
        p.x *= 2;
        p.y *= 2;
        Point q(2'000'000'005, p.y + 1);
        int crosses = 0;
        for (int i = 0; i < n; i++) {
            if (on_line(poly[i], poly[(i + 1) % n], p)) {
                cout << "BOUNDARY\n";
                goto out;
            }
            crosses += intersect(p, q, poly[i], poly[(i + 1) % n]);
        }

        if (crosses & 1) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";

        out:;
    }
}