#include <bits/stdc++.h>
using namespace std;

set<array<int, 3>> cells;
set<array<int, 3>> visited;
set<array<int, 3>> done;

template<bool _x, bool _y, bool _z>
void dfs(int x, int y, int z) {
    if (!cells.count({x, y, z})) return;
    if (visited.count({x, y, z})) return;
    visited.insert({x, y, z});

    if (_x) {
        dfs<_x, _y, _z>(x + 1, y, z);
        dfs<_x, _y, _z>(x - 1, y, z);
    }
    
    if (_y) {
        dfs<_x, _y, _z>(x, y + 1, z);
        dfs<_x, _y, _z>(x, y - 1, z);
    }

    if (_z) {
        dfs<_x, _y, _z>(x, y, z + 1);
        dfs<_x, _y, _z>(x, y, z - 1);
    }
}

template<bool _x, bool _y, bool _z>
bool check() {
    visited.clear();
    done.clear();

    for (auto [x, y, z]: cells) {
        if (visited.count({x, y, z})) continue;

        array<int, 3> id = {_x ? -1 : x, _y ? -1 : y, _z ? -1 : z};
        if (done.count(id)) return false;
        done.insert(id);

        dfs<_x, _y, _z>(x, y, z);
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<int> X(N), Y(N), Z(N);
    for (auto &x: X) cin >> x;
    for (auto &y: Y) cin >> y;
    for (auto &z: Z) cin >> z;

    for (int i = 0; i < N; i++) {
        cells.insert({X[i], Y[i], Z[i]});
    }

    bool ok = true;
    ok &= check<1, 1, 1>();
    ok &= check<1, 1, 0>();
    ok &= check<1, 0, 1>();
    ok &= check<0, 1, 1>();
    ok &= check<1, 0, 0>();
    ok &= check<0, 1, 0>();
    ok &= check<0, 0, 1>();

    cout << (ok ? "YES\n" : "NO\n");
}