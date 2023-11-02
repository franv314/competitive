#include <bits/stdc++.h>
using namespace std;
 
struct pt {
    long long x, y;
};
 
pt operator-(pt x, pt y) {
    return {x.x - y.x, x.y - y.y};
}
 
long long cross(pt x, pt y) {
    return x.x * y.y - x.y * y.x;
}
 
long long orient(pt o, pt a, pt b) {
    return cross(a - o, b - o);
}
 
int main() {
    int N; cin >> N;
    vector<pt> points(N);
    
    for (auto &[x, y]: points) cin >> x >> y;
    sort(points.begin(), points.end(), [](pt a, pt b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    
    vector<pt> hull;
    for (int _ = 0; _ < 2; _++) {
        for (auto p: points) {
            while  (hull.size() > 1 && orient(hull[hull.size() - 2], hull[hull.size() - 1], p) > 0)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    cout << hull.size() << "\n";
    for (auto [x, y]: hull) cout << x << " " << y << "\n";
}