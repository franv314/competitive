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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int x1, y1, x2, y2, x3, y3; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3);

        switch (orient(p1, p2, p3)) {
        case +1: cout << "LEFT\n"; break;
        case  0: cout << "TOUCH\n"; break;
        case -1: cout << "RIGHT\n"; break;
        }
    }
}