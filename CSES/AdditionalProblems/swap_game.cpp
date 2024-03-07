#include <bits/stdc++.h>
using namespace std;

long long encode(const array<int, 9> &val) {
    long long ret = 0;
    for (int i = 0; i < 9; i++) {
        ret |= (long long)val[i] << (4 * i);
    }
    return ret;
}

array<int, 9> decode(long long val) {
    array<int, 9> ret;
    for (int i = 0; i < 9; i++) {
        ret[i] = (val >> (4 * i)) & 15;
    }
    return ret;
}

int main() {
    array<int, 9> st;
    for (auto &x: st) cin >> x;

    unordered_set<long long> visited;
    queue<pair<long long, int>> q;

    q.emplace(encode({1, 2, 3, 4, 5, 6, 7, 8, 9}), 0);
    while (!q.empty()) {
        auto [pos, dst] = q.front(); q.pop();
        if (visited.count(pos)) continue;
        visited.insert(pos);

        array<int, 9> grid = decode(pos);
        if (grid == st) {
            cout << dst << '\n';
            return 0;
        }

        for (auto x: {0, 1, 2, 3, 4, 5}) {
            swap(grid[x], grid[x + 3]);
            q.emplace(encode(grid), dst + 1);
            swap(grid[x], grid[x + 3]);
        }
        for (auto x: {0, 1, 3, 4, 6, 7}) {
            swap(grid[x], grid[x + 1]);
            q.emplace(encode(grid), dst + 1);
            swap(grid[x], grid[x + 1]);
        }
    }
}