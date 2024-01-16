#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    vector<int> arr(n), pos_of(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pos_of[--arr[i]] = i;
    }

    auto where = [&](int val) {
        if (val < 0) return INT_MAX;
        if (val >= n) return INT_MAX;
        return pos_of[val];
    };

    int tot = 0;
    for (int i = 0; i < n; i++) {
        tot += where(i) < where(i - 1);
    }

    while (m--) {
        int a, b; cin >> a >> b;
        a--, b--;

        set<int> updates;
        updates.insert(arr[a]);
        updates.insert(arr[a] + 1);
        updates.insert(arr[b]);
        updates.insert(arr[b] + 1);

        for (auto upd: updates) tot -= where(upd) < where(upd - 1);

        swap(pos_of[arr[a]], pos_of[arr[b]]);
        swap(arr[a], arr[b]);

        for (auto upd: updates) tot += where(upd) < where(upd - 1);

        cout << tot << '\n';
    }
}