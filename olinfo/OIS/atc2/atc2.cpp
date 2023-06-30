#include <bits/stdc++.h>
using namespace std;

#define MAXN 3000

struct Point {
    int x, y;
};

int dst(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int N;
vector<Point> towers;

int find_min(vector<int> d, vector<bool> mst) {
    int min = INT_MAX, min_idx;
    for (int i = 0; i < d.size(); i++)
        if (!mst[i] && d[i] < min)
            min = d[min_idx = i];
    return min_idx;
}

int prim() {
    int T = towers.size();
    int mst_size = 0;

    vector<bool> mst(T, false);
    vector<int> d(T, INT_MAX);
    vector<int> par(TMP_MAX, -1);

    d[0] = 0;

    for (int _ = 1; _ < T; _++) {
        int curr = find_min(d, mst);

        mst[curr] = true;
        for (int i = 0; i < T; i++) {
            int _d = dst(towers[i], towers[curr]);
            if (!mst[i] && _d < d[i]) {
                d[i] = _d;
                par[i] = curr;
            }
        }
    }
    for (int i = 1; i < T; i++)
        mst_size += dst(towers[i], towers[par[i]]);
    return mst_size;
}

int main() {
    assert(1 == scanf("%d", &N));
    for(int i = 0; i < N; i++) {
        getchar();
        for (int j = 0; j < N; j++)
            if (getchar() == 'T')
                towers.push_back({i, j});
    }

    printf("%d\n", prim()); // print the result 
    return 0;
}