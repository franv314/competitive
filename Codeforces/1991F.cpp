#include <bits/stdc++.h>
using namespace std;

constexpr int CUT = 100;

int bitmasks[] = {
    0b111000,
    0b110100,
    0b110010,
    0b110001,
    0b101100,
    0b101010,
    0b101001,
    0b100110,
    0b100101,
    0b100011,
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    while (q--) {
        int l, r; cin >> l >> r;
        l--;

        if (r - l >= CUT) {
            cout << "YES\n";
            continue;
        }

        vector<int> query(a.begin() + l, a.begin() + r);
        sort(query.rbegin(), query.rend());
        bool ok = false;

        for (int i = 0; i <= query.size() - 6; i++) {
            for (auto mask: bitmasks) {
                int idx[2] = {};
                int tri[2][3] = {};

                for (int j = 0; j < 6; j++) {
                    int x = (mask >> j) & 1;
                    tri[x][idx[x]++] = query[i + j];
                }

                if (tri[0][0] < tri[0][1] + tri[0][2] && tri[1][0] < tri[1][1] + tri[1][2]) {
                    ok = true;
                    break;
                }
            }
        }

        int earliest = 1e9;
        for (int i = 0; i <= query.size() - 3; i++) {
            if (query[i] < query[i + 1] + query[i + 2]) {
                if (earliest <= i - 3) {
                    ok = true;
                    break;
                } else if (earliest == 1e9) {
                    earliest = i;
                }
            }
        }

        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
}