#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    map<int, set<int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        events[a].insert(i);
        events[b + 1].insert(-i);
    }

    set<int> rooms;
    map<int, int> which;
    vector<int> ans(n);    
    for (auto [_, l]: events) {
        for (auto x: l) {
            if (x < 0) {
                rooms.insert(which[-x]);
                which.erase(-x);
            } else {
                if (rooms.empty()) {
                    rooms.insert(which.size() + 1);
                }
                ans[x - 1] = which[x] = *rooms.begin();
                rooms.erase(rooms.begin());
            }
        }
    }

    cout << rooms.size() << '\n';
    for (auto x: ans) cout << x << ' '; cout << '\n';
}