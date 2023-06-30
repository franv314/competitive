#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int M, F; cin >> M >> F;
    int C; cin >> C;

    vector<vector<int>> cotte(M);
    for (int i = 0; i < C; i++) {
        int a, b; cin >> a >> b;
        cotte[a - 1].push_back(b - 1);
    }

    vector<int> sequence;
    for (auto c: cotte) {
        sort(c.rbegin(), c.rend());
        for (auto x: c) sequence.push_back(x);
    }

    vector<int> lowest_val(C + 1, INT_MAX);
    lowest_val[0] = INT_MIN;

    int ans = 0;

    for (int i = 0; i < C; i++) {
        int best = lower_bound(lowest_val.begin(), lowest_val.end(), sequence[i]) - lowest_val.begin();
        lowest_val[best] = min(lowest_val[best], sequence[i]);

        ans = max(ans, best);
    }
    cout << 2 * ans;
}