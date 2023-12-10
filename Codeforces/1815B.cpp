#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    if (n == 2) {
        cout << "! 1 2 2 1" << endl;
        int ans; cin >> ans;
        if (ans == -2) exit(0);
        return;
    }

    vector<int> order(n);

    if (n & 1) {
        cout << "+ " << n << endl;
        int ans; cin >> ans;
        if (ans == -2) exit(0);

        cout << "+ " << n + 2 << endl;
        cin >> ans;
        if (ans == -2) exit(0);

        order[0] = n;

        for (int i = 1; i < n; i++) {
            int try_1 = n + 2 - order[i - 1];
            int try_2 = n - order[i - 1];
            if (try_1 > 0 && try_1 != order[i - 2]) {
                order[i] = try_1;
            } else {
                order[i] = try_2;
            }
        }
    } else {
        cout << "+ " << n - 1 << endl;
        int ans; cin >> ans;
        if (ans == -2) exit(0);
        
        cout << "+ " << n + 1 << endl;
        cin >> ans;
        if (ans == -2) exit(0);

        order[0] = n - 1;

        for (int i = 1; i < n; i++) {
            int try_1 = n + 1 - order[i - 1];
            int try_2 = n - 1 - order[i - 1];
            if (try_1 > 0 && try_1 != order[i - 2]) {
                order[i] = try_1;
            } else {
                order[i] = try_2;
            }
        }
    }

    pair<int, int> ma = {-1, -1};
    for (int i = 2; i <= n; i++) {
        cout << "? 1 " << i << endl;
        int ans; cin >> ans;
        if (ans == -2) exit(0);
        ma = max(ma, {ans, i});
    }

    vector<int> dist_of(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == ma.second) continue;
        cout << "? " << ma.second << " " << i << endl;
        cin >> dist_of[i];
        if (dist_of[i] == -2) exit(0);
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << order[dist_of[i]] << " ";
    }

    reverse(order.begin(), order.end());
    for (int i = 1; i <= n; i++) {
        cout << order[dist_of[i]] << " ";
    }
    cout << endl;

    int ans; cin >> ans;
    if (ans == -2) exit(0);
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
