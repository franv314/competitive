#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    long long operator^(const Point &other) const { return (long long)x * other.y - (long long)y * other.x; }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    Point first, last;
    cin >> first.x >> first.y;
    last = first;

    long long area = 0;
    long long border = 0;

    for (int _ = 1; _  < n; _++) {
        Point t; cin >> t.x >> t.y;
        area += t ^ last;
        border += gcd(abs(t.x - last.x), abs(t.y - last.y));
        last = t;
    }

    area += first ^ last;
    border += gcd(abs(first.x - last.x), abs(first.y - last.y));

    long long inside = (abs(area) + 2 - border) / 2;

    cout << inside << ' ' << border << '\n';
}