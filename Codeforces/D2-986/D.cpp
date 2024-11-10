#include <bits/stdc++.h>
using namespace std;

char conv[3] = {'q', 'k', 'j'};

void solve() {
    int n; cin >> n;
    vector<vector<int>> p(3, vector<int>(n));

    for (auto &row: p) {
        for (auto &x: row)
            cin >> x;
    
        vector<int> order(n);
        for (int i = 0; i < n; i++)
            order[row[i] - 1] = i;
        row = order;
    }

    vector<pair<int, int>> how(n, {-1, -1});
    how[0] = {-2, -2};
    vector<int> pos = {0, 0, 0};

    vector<set<int>> seen(3);

    set<int> moves;
    moves.insert(0);

    while (!moves.empty()) {
        set<int> new_moves;

        for (int i: {0, 1, 2}) {
            set<int> curr_moves;
            for (auto x: moves)
                if (!seen[i].count(x))
                    curr_moves.insert(x);

            while (pos[i] < n && !curr_moves.empty()) {
                int v = p[i][pos[i]];
                seen[i].insert(v);
                curr_moves.erase(v);

                if (!curr_moves.empty() && how[v] == make_pair(-1, -1) && v > *curr_moves.begin()) {
                    how[v] = {i, *curr_moves.begin()}; 
                    new_moves.insert(v);   
                }

                pos[i]++;
            }
        }

        moves = new_moves;
    }

    if (how[n - 1] == make_pair(-1, -1)) {
        return void(cout << "NO\n");
    }

    vector<pair<int, int>> mov;
    for (int curr = n - 1; curr != 0; curr = how[curr].second) {
        mov.emplace_back(how[curr].first, curr);
    }
    reverse(mov.begin(), mov.end());

    cout << "YES\n";
    cout << mov.size() << '\n';
    for (auto [x, y]: mov) {
        cout << conv[x] << " " << y + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
