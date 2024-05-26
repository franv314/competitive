#include <bits/stdc++.h>
using namespace std;

#define MAXD 2'000'001

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N, M; in >> N >> M;

    vector<pair<int, int>> pairs;
    pairs.reserve(2 * N);

    for (int i = 0; i < N; i++) {
        int x, y; in >> x >> y;
        pairs.emplace_back(x, y);
        pairs.emplace_back(y, x);
    }
    sort(pairs.begin(), pairs.end());

    int curr = 0;
    vector<bool> seen(MAXD);

    int pos = 0;
    for (;;) {
        auto next_teleporter = upper_bound(pairs.begin(), pairs.end(), make_pair(pos, INT_MAX));
        if (next_teleporter == pairs.end()) break;

        curr++;
        seen[next_teleporter->first] = true;
        pos = next_teleporter->second;
    }

    vector<int> cycles;
    for (auto [x, _]: pairs) {
        if (seen[x]) continue;

        int start = x;
        bool cycled = false;
        int len = 0;

        int pos = start - 1;
        for (;;) {
            auto next_teleporter = upper_bound(pairs.begin(), pairs.end(), make_pair(pos, INT_MAX));
            if (next_teleporter->first == start && cycled) {
                seen[start] = true;
                break;
            }

            len++;
            if (cycled) seen[next_teleporter->first] = true;
            pos = next_teleporter->second;

            cycled = true;
        }

        cycles.push_back(len);
    }

    sort(cycles.begin(), cycles.end());
    while (!cycles.empty() && M-- > 0) {
        curr += cycles.back() + 2;
        cycles.pop_back();
    }

    bool odd = false;
    while (M-- > 0) {
        if (!odd) curr++;
        else curr += 3;
        odd = !odd;
    }

    out << curr << '\n';
}