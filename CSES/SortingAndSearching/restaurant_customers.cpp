#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<pair<int, int>> events;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        events.emplace_back(a, 1);
        events.emplace_back(b + 1, -1);
    }

    sort(events.begin(), events.end());
    int curr = 0;
    int ma = 0;
    
    for (auto [_, x]: events) {
        ma = max(ma, curr += x);
    }

    cout << ma << '\n';
}