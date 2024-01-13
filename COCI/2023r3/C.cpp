#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<array<int, 2>> trains(n);
    for (int i = 0; i < n; i++) cin >> trains[i][0];
    for (int i = 0; i < n; i++) cin >> trains[i][1];

    sort(trains.begin(), trains.end());

    set<int> lis;
    for (auto [a, b]: trains) {
        auto [it, ok] = lis.insert(b);
        if (next(it) != lis.end()) lis.erase(next(it));
    }

    cout << lis.size() << '\n';
}