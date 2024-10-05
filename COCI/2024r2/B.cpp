#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    int x0, y0, z0; cin >> y0 >> z0 >> x0;
    int x1, y1, z1; cin >> y1 >> z1 >> x1;

    vector space(n, vector<string>(n));
    for (auto &grid: space)
        for (auto &row: grid)
            cin >> row;

    vector dst(n, vector(n, vector(n, -1)));
    queue<tuple<int, int, int, int>> q;
    q.emplace(x0 - 1, y0 - 1, z0 - 1, 0);

    while (!q.empty()) {
        auto [x, y, z, d] = q.front(); q.pop();
        if (dst[x][y][z] != -1) continue;
        dst[x][y][z] = d;

        if (x + 1 < n && space[x + 1][y][z] == '0') q.emplace(x + 1, y, z, d + 1);
        if (y + 1 < n && space[x][y + 1][z] == '0') q.emplace(x, y + 1, z, d + 1);
        if (z + 1 < n && space[x][y][z + 1] == '0') q.emplace(x, y, z + 1, d + 1);
        if (x - 1 >= 0 && space[x - 1][y][z] == '0') q.emplace(x - 1, y, z, d + 1);
        if (y - 1 >= 0 && space[x][y - 1][z] == '0') q.emplace(x, y - 1, z, d + 1);
        if (z - 1 >= 0 && space[x][y][z - 1] == '0') q.emplace(x, y, z - 1, d + 1);
    }

    cout << dst[x1 - 1][y1 - 1][z1 - 1] << '\n';
}