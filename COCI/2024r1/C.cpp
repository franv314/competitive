#include <bits/stdc++.h>
using namespace std;

struct Seg1D {
    vector<int> arr;
    int s;

    int query(int l, int r) {
        int ans = INT_MIN;
        for (l += s, r += s; l < r; r >>= 1, l >>= 1) {
            if (l & 1) ans = max(ans, arr[l++]);
            if (r & 1) ans = max(ans, arr[--r]);
        }
        return ans;
    }

    Seg1D() {}
    Seg1D(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++) arr[i + s] = a[i];
        for (int i = s - 1; i; i--) arr[i] = max(arr[2 * i], arr[2 * i + 1]);
    }
};

struct Seg2D {
    vector<Seg1D> arr;
    int s;

    int query(int l, int r, int t, int b) {
        int ans = INT_MIN;
        for (t += s, b += s; t < b; t >>= 1, b >>= 1) {
            if (t & 1) ans = max(ans, arr[t++].query(l, r));
            if (b & 1) ans = max(ans, arr[--b].query(l, r));
        }
        return ans;
    }

    Seg2D(const vector<vector<int>> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        vector<vector<int>> arrs(2 * s, vector<int>(a.front().size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++) {
            arrs[i + s] = a[i];
            arr[i + s] = Seg1D(arrs[i + s]);
        }
        for (int i = s - 1; i; i--) {
            for (int j = 0; j < a.front().size(); j++) {
                arrs[i][j] = max(arrs[2 * i][j], arrs[2 * i + 1][j]);
            }
            arr[i] = Seg1D(arrs[i]);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> arr(n, vector<int>(m));
    for (auto &row: arr)
        for (auto &el: row)
            cin >> el;

    Seg2D segment(arr);

    int x, y; cin >> x >> y;
    for (int t = 0; t <= n - x; t++) {
        for (int l = 0; l <= m - y; l++) {
            int ma = segment.query(l, l + y, t, t + x);
            cout << ma << ' ';
        }
        cout << '\n';
    }
}