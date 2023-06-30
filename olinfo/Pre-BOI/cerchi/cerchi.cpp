#include <bits/stdc++.h>
using namespace std;

struct Point {
    int idx;
    long long x;
    long long y;
};

inline long long sqr_dist(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline bool operator<(Point a, Point b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

inline bool operator==(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

inline long long turn_dir(Point P1, Point P2, Point P3) {
    return (P2.x - P1.x) * (P3.y - P1.y) - (P2.y - P1.y) * (P3.x - P1.x);
}

vector<int> trovacerchi(int N, vector<int> X, vector<int> Y) {
    vector<Point> points(N + 1);
    points[0] = {-1, 0, 0};
    for (int i = 0; i < N; i++)
        points[i + 1] = {i, X[i], Y[i]};
    
    Point min_point = points[0];
    int min_idx = 0;
    for (int i = 1; i <= N; i++)
        if (points[i] < min_point)
            min_point = points[min_idx = i];
    
    swap(points[0], points[min_idx]);

    sort(points.begin() + 1, points.end(), [&](Point a, Point b){
        long long orient = turn_dir(min_point, a, b);
        if (orient == 0) return sqr_dist(min_point, a) < sqr_dist(min_point, b);
        return orient > 0;
    });

    int j = 1;
    for (int i = 1; i < N; i++)
        if (turn_dir(min_point, points[i], points[i + 1]))
            points[j++] = points[i];

    points[j++] = points[N];
    points.resize(j);

    vector<Point> hull = {};
    for (auto point: points) {
        while (hull.size() > 1 && turn_dir(hull[hull.size() - 2], hull[hull.size() - 1], point) <= 0)
            hull.pop_back();
        hull.push_back(point);
    }
    vector<int> hull_idx = {};
    for (auto point: hull)
        if (point.idx >= 0)
            hull_idx.push_back(point.idx);
    return hull_idx;
}