#include <bits/stdc++.h>
using namespace std;

int main() {
    map<pair<int, int>, vector<pair<int, int>>> res;
    vector<pair<int, int>> g;

    function<void(int, int, int, int)> rec = [&](int pta, int ptb, int sta, int stb) {
        if (stb == 3) {
            return;
        }
        if (sta == 3) {
            res[{pta, ptb}] = g;
            return;
        }

        for (int i = 0; i <= 10; i++) {
            g.emplace_back(11, i);
            rec(pta + 11, ptb + i, sta + 1, stb);
            g.pop_back();
            g.emplace_back(i, 11);
            rec(pta + i, ptb + 11, sta, stb + 1);
            g.pop_back();
        }
    };

    rec(0, 0, 0, 0);
    int T; cin >> T;
    while (T--) {
        int A, B; cin >> A >> B;
        if (!res.count({A, B})) cout << "-1 -1\n";
        else {
            auto x = res[{A, B}];
            for (auto [r, rr]: x) cout << r << " " << rr << "\n";
        }
    }
}