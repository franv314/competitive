#include <bits/stdc++.h>
using namespace std;

struct Move {
    int x, y;

    Move(int x, int y) : x(x), y(y) { }
    Move() : Move(0, 0) { }
};

Move operator+(Move a, Move b) {
    return {a.x + b.x, a.y + b.y};
}

Move operator-(Move a) {
    return {-a.x, -a.y};
}

Move L(-1, 0);
Move R(+1, 0);
Move U(0, +1);
Move D(0, -1);

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;

    vector<Move> ps(n + 1), ips(n + 1);
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
        case 'L': ps[i + 1] = ps[i] + L; break;
        case 'R': ps[i + 1] = ps[i] + R; break;
        case 'U': ps[i + 1] = ps[i] + U; break;
        case 'D': ps[i + 1] = ps[i] + D; break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        switch (s[i]) {
        case 'L': ips[i] = ips[i + 1] + L; break;
        case 'R': ips[i] = ips[i + 1] + R; break;
        case 'U': ips[i] = ips[i + 1] + U; break;
        case 'D': ips[i] = ips[i + 1] + D; break;
        }
    }

    map<pair<int, int>, set<int>> prefix, iprefix;
    for (int i = 0; i <= n; i++) prefix[{ps[i].x, ps[i].y}].insert(i);
    for (int i = 0; i <= n; i++) iprefix[{ips[i].x, ips[i].y}].insert(i);

    while (q--) {
        int x, y, l, r; cin >> x >> y >> l >> r;
        l--;

        Move target_1(x, y);
        auto pos = prefix[{target_1.x, target_1.y}].begin();

        if (pos != prefix[{target_1.x, target_1.y}].end() && *pos <= l) {
            cout << "YES\n";
            continue;
        }

        Move target_2 = target_1 + (-ps[l]) + ips[r];
        auto pos2 = iprefix[{target_2.x, target_2.y}].lower_bound(l);

        if (pos2 != iprefix[{target_2.x, target_2.y}].end() && *pos2 <= r) {
            cout << "YES\n";
            continue;
        }

        Move target_3 = target_1 + (-ps[l]) + ips[r] + (-ips[l]) + ps[r];
        auto pos3 = prefix[{target_3.x, target_3.y}].lower_bound(r);

        if (pos3 != prefix[{target_3.x, target_3.y}].end()) {
            cout << "YES\n";
            continue;
        }

        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}