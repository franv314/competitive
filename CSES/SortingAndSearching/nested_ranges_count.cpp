#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    map<int, vector<pair<int, int>>> ranges_up;
    map<int, vector<pair<int, int>>, greater<int>> ranges_down;
    tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ends;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        ranges_up[a].emplace_back(b, i);
        ranges_down[a].emplace_back(b, i);
    }

    vector<int> contains(n), contained(n);

    for (auto [a, upd]: ranges_up) {
        for (auto [b, i]: upd) ends.insert(b);
        for (auto [b, i]: upd) {
            contained[i] = ends.size() - ends.order_of_key(b) - 1;
        }
    }

    ends.clear();
    for (auto [a, upd]: ranges_down) {
        for (auto [b, i]: upd) ends.insert(b);
        for (auto [b, i]: upd) {
            contains[i] = ends.order_of_key(b + 1) - 1;
        }
    }

    for (auto x: contains) cout << x << ' '; cout << '\n';
    for (auto x: contained) cout << x << ' '; cout << '\n';
}