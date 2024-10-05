#include <bits/stdc++.h>
using namespace std;

int am[200];

int score(int k, int r, int o, int d) {
    return k * k + r * r + o * o + d * d + 7 * min({k / 2, o / 2, d, r});
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    string s; cin >> s;
    
    for (auto c: s) am[c]++;

    int ma = 0;
    for (int k = 0; k <= m; k++) {
        for (int r = 0; k + r <= m; r++) {
            for (int o = 0; k + r + o <= m; o++) {
                int d = m - k - r - o;

                ma = max(ma, score(am['k'] + k, am['r'] + r, am['o'] + o, am['d'] + d));
            }
        }
    }
    cout << ma << "\n";
}