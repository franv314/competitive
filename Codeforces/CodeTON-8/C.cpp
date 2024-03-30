#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x, y; cin >> n >> x >> y;
    vector<int> a(x);
    for (auto &x: a) {
        cin >> x;
        x--;
    }

    sort(a.begin(), a.end());
    priority_queue<int, vector<int>, greater<int>> even, odd;

    for (int i = 0; i < x; i++) {
        int diff = (a[i] - a[(i - 1 + x) % x] + n) % n;

        if (diff & 1) odd.push(diff);
        else even.push(diff);
    }

    int used = 0, new_cnt = 0;
    while (!even.empty()) {
        int z = even.top(); even.pop();

        int might_add = (z - 1) / 2;
        int will_add = min(might_add, y - used);

        used += will_add;
        new_cnt += will_add;

        if (will_add == might_add) new_cnt++;
    }

    while (!odd.empty()) {
        int z = odd.top(); odd.pop();

        int might_add = z / 2;
        int will_add = min(might_add, y - used);

        used += will_add;
        new_cnt += will_add;
    }

    cout << x + used - 2 + new_cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}