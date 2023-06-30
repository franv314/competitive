#include <bits/stdc++.h>
using namespace std;

int solve(vector<pair<int, int>> pointss) {
    pointss.push_back({INT_MAX, INT_MIN});

    vector<pair<int, int>> points;
    for (int i = 0; i < pointss.size(); i++) {
        auto it = upper_bound(points.begin(), points.end(), pointss[i]);
        points.insert(it, pointss[i]);
        
        for (int j = 1; j <= i; j++)
            if (points[j - 1].second > points[j].second)
                return i;
    }
}

int main() {
    int t; cin >> t;
    vector<future<int>> threads(t);

    for (auto &th: threads) {
        int n; cin >> n;
        vector<pair<int, int>> points(n);
        for (auto &[x, y]: points) cin >> x >> y;
        
        th = async(solve, points);
    }

    for (int i = 0; i < t; i++) {
        cout << "Case #" << i + 1 << ": " << threads[i].get() << endl;
    }
}