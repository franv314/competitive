#include <bits/stdc++.h>
using namespace std;

#define SIZE 100

struct Point {
    int x, y;
   
    bool operator==(const Point &o) const { return tie(x, y) == tie(o.x, o.y); }
    Point operator-(const Point &o) const { return {x - o.x , y - o.y}; }
    int operator^(const Point &o) const { return x * o.y - y * o.x; }
};

int orient(const Point &o, const Point &p, const Point &q) {
    int cross = (p - o) ^ (q - o);
    if (cross > 0) return +1;
    if (cross < 0) return -1;
    return 0;
}

int main() {
    int N; cin >> N;
    vector<pair<int, int>> points(N);
    for (auto &[x, y]: points) {
        cin >> x >> y;
        x *= 2;
        y *= 2;
    }

    int ans = 0;
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            int cnt = 0;
            for (int i = 0; i < N; i++) {
                auto [x1, y1] = points[i];
                auto [x2, y2] = points[(i + 1) % N];

                int cx = 2 * x + 1;
                int cy = 2 * y + 1;

                if (
                    max(x1, x2) >= cx + 1 && min(x1, x2) <= cx - 1 &&
                    max(y1, y2) >= cy + 1 && min(y1, y2) <= cy - 1
                ) {
                    bool freq[3] = {};
                    freq[orient({x1, y1}, {x2, y2}, {cx - 1, cy - 1}) + 1] = true;
                    freq[orient({x1, y1}, {x2, y2}, {cx - 1, cy + 1}) + 1] = true;
                    freq[orient({x1, y1}, {x2, y2}, {cx + 1, cy - 1}) + 1] = true;
                    freq[orient({x1, y1}, {x2, y2}, {cx + 1, cy + 1}) + 1] = true; 

                    if (freq[0] && freq[2]) {
                        cnt = 0;
                        break;
                    }
                }

                if (x1 == x2) continue;
                if (!(x1 <= cx && cx <= x2) && !(x2 <= cx && cx <= x1)) continue;

                double h = y1 + (double)(cx - x1) / (x2 - x1) * (y2 - y1);
                cnt += (h < cy);
            }

            ans += cnt & 1;
        }
    }

    cout << ans << '\n';
}