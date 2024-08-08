#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

struct Ship {
    int x, y;
    char dir;

    int dist(const Ship &o) const { return abs(x - o.x) + abs(y - o.y); }
};

enum { N, E, S, W };

int dir_num(char dir) {
    switch (dir) {
        case 'N': return N;
        case 'E': return E;
        case 'S': return S;
        case 'W': return W;
    }
}

#define LEFT(dir, card, repr, discr) \
    it = (dir)[card][repr].lower_bound(discr); \
    if (it != (dir)[card][repr].begin() && !(dir)[card][repr].empty()) \
        add_crash(ship, prev(it)->second);

#define RIGHT(dir, card, repr, discr) \
    it = (dir)[card][repr].upper_bound(discr); \
    if (it != (dir)[card][repr].end()) \
        add_crash(ship, it->second);

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<Ship> ships(n);
    for (auto &[x, y, dir]: ships)
        cin >> x >> y >> dir;

    gp_hash_table<int, map<int, int>> hor[4], ver[4], diagp[4], diagm[4];
    
    for (int i = 0; i < n; i++) {
        auto [x, y, dir] = ships[i];
        int d = dir_num(dir);
        hor[d][y][x] = i;
        ver[d][x][y] = i;
        diagp[d][x + y][x] = i;
        diagm[d][x - y][x] = i;
    }

    map<int, vector<pair<int, int>>> crashes;

    auto add_crash = [&](int u, int v) {
        crashes[ships[u].dist(ships[v])].emplace_back(u, v);
    };

    auto next_crash = [&](int ship) {
        auto [x, y, dir] = ships[ship];
        vector<int> crashes;
        map<int, int>::iterator it;

        switch (dir) {
            case 'N':
                LEFT(ver, S, x, y);
                LEFT(diagm, E, x - y, x);
                RIGHT(diagp, W, x + y, x);
                return;
            case 'E':
                RIGHT(hor, W, y, x);
                RIGHT(diagp, S, x + y, x);
                return;
            case 'S':
                RIGHT(diagm, W, x - y, x);
                return;
        }
    };

    for (int i = 0; i < n; i++) {
        next_crash(i);
    }

    vector<bool> alive(n, true);

    while (!crashes.empty()) {
        set<int> boomships;
        for (auto [x, y]: crashes.begin()->second) {
            if (!alive[x] || !alive[y]) continue;
            boomships.insert(x);
            boomships.insert(y);
        }

        for (auto ship: boomships) {
            alive[ship] = false;

            auto [x, y, dir] = ships[ship];
            int d = dir_num(dir);
            hor[d][y].erase(x);
            ver[d][x].erase(y);
            diagp[d][x + y].erase(x);
            diagm[d][x - y].erase(x);

            for (auto dir: {hor, ver, diagp, diagm}) {
                for (int card = 0; card < 4; card++) {
                    int discr = dir == ver ? y : x;
                    
                    int repr;
                    if (dir == hor) repr = y;
                    if (dir == ver) repr = x;
                    if (dir == diagp) repr = x + y;
                    if (dir == diagm) repr = x - y;

                    {
                        auto it = dir[card][repr].upper_bound(discr);
                        if (it != dir[card][repr].end()) {
                            next_crash(it->second);
                        }
                    }
                    {
                        auto it = dir[card][repr].lower_bound(discr);
                        if (it != dir[card][repr].begin() && !dir[card][repr].empty()) {
                           next_crash(prev(it)->second);
                        }
                    }
                }
            }
        }

        crashes.erase(crashes.begin());
    }

    for (int i = 0; i < n; i++)
        if (alive[i])
            cout << i + 1 << '\n';
}