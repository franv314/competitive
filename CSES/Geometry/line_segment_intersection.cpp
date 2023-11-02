#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    long long operator^(const Point &other) const { return (long long)x * other.y - (long long)y * other.x; }
};

int orient(const Point &o, const Point &p, const Point &q) {
    long long cross = (p - o) ^ (q - o);
    if (cross == 0) return 0;
    if (cross > 0) return 1;
    return -1;
}

bool operator<(const Point &a, const Point &b) { return tie(a.x, a.y) < tie(b.x, b.y); }
bool operator>(const Point &a, const Point &b) { return tie(a.x, a.y) > tie(b.x, b.y); }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int x1, y1, x2, y2, x3, y3, x4, y4; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);

        int or_1 = orient(p1, p2, p3);
        int or_2 = orient(p1, p2, p4);
        int or_3 = orient(p3, p4, p1);
        int or_4 = orient(p3, p4, p2);

        if (!or_1 && !or_2 && !or_3 && !or_4) {
            if (p1 < p3 && p2 < p3 && p1 < p4 && p2 < p4) {
                cout << "NO\n";
            } else if (p1 > p3 && p2 > p3 && p1 > p4 && p2 > p4) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        } else {
            if (or_1 != or_2 && or_3 != or_4) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}