#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

struct Color {
    struct Point {
        int x, y;
    } a, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Color> lights(k);
    for (int i = 0; i < k; i++)
        cin >> lights[i].a.x >> lights[i].a.y >> lights[i].b.x >> lights[i].b.y;

    int count = 0;
    for (int min_x = 0; min_x <= n; min_x++) {
        for (int max_x = min_x + 1; max_x <= n; max_x++) {
            for (int min_y = 0; min_y <= m; min_y++) {
                for (int max_y = min_y + 1; max_y <= m; max_y++) {
                    for (auto color: lights) {
                        bool fst = min_x <= color.a.x && color.a.x <= max_x && min_y <= color.a.y && color.a.y <= max_y;
                        bool snd = min_x <= color.b.x && color.b.x <= max_x && min_y <= color.b.y && color.b.y <= max_y;
                        if (fst != snd) goto next;
                    }
                    count++;
                    next:;
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}