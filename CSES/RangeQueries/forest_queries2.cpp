#include <bits/stdc++.h>
using namespace std;

struct Fenwick2D {
    vector<vector<int>> mat;

    void add(int X, int Y, int d) {
        for (int x = X; x < mat.size(); x += x & -x)
            for (int y = Y; y < mat.size(); y += y & -y)
                mat[x][y] += d;
    }

    int sum(int X, int Y) {
        int ans = 0;
        for (int x = X; x; x -= x & -x)
            for (int y = Y; y; y -= y & -y)
                ans += mat[x][y];
        return ans;
    }

    Fenwick2D(int size) : mat(size + 1, vector<int>(size + 1)) { }
};

int main() {
    int n, q; cin >> n >> q;
    vector<string> grid(n);
    Fenwick2D fenwick(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            fenwick.add(i + 1, j + 1, grid[i][j] == '*');
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, j; cin >> i >> j;
            if (grid[i - 1][j - 1] == '*') {
                fenwick.add(i, j, -1);
                grid[i - 1][j - 1] = '.';
            } else {
                fenwick.add(i, j, +1);
                grid[i - 1][j - 1] = '*';
            }
        } else {
            int i1, j1, i2, j2; cin >> i1 >> j1 >> i2 >> j2;
            cout << fenwick.sum(i2, j2) - fenwick.sum(i1 - 1, j2) - fenwick.sum(i2, j1 - 1) + fenwick.sum(i1 - 1, j1 - 1) << '\n';
        }
    }
}