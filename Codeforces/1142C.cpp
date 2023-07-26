#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Point {
    i64 x, y;
    
    Point() { }
    Point(i64 x, i64 y) : x(x), y(y) { }
};

Point operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
i64 cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
strong_ordering orient(Point o, Point a, Point b) { return cross(a - o, b - o) <=> 0; }

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    int n; cin >> n;
    vector<Point> points(n);
    for_each(points.begin(), points.end(), [](Point &a) {
        cin >> a.x >> a.y;
        a.y -= a.x * a.x;
    });
    
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });
    
    vector<Point> hull;
    for_each(points.begin(), points.end(), [&](Point p) {
        while (
            (hull.size() >= 2 && orient(hull[hull.size() - 2], hull[hull.size() - 1], p) >= 0) ||
            (hull.size() >= 1 && hull.back().x == p.x)   
        ) hull.pop_back();
        hull.push_back(p);
    });
    
    cout << hull.size() - 1 << '\n';
}