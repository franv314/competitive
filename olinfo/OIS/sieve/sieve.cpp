#include <bits/stdc++.h>
using namespace std;

#define MAXN 500
#define INF 1000

int N, M, V[MAXN];
bitset<MAXN> keeps[MAXN];

int start;
int best = INF;

unordered_map<bitset<MAXN>, int> known;

int dfs(bitset<MAXN> status, int depth = 0) {
    if (known.find(status) != known.end()) {
        best = min(best, depth + known[status]);
        return known[status];
    }
    if (!status.any()) {
        best = min(best, depth);
        known[status] = 0;
        return 0;
    }
    if (depth >= best - 1) {
        return INF;
    }
    if (clock() - start > 0.58 * CLOCKS_PER_SEC) {
        cout << best;
        exit(0);
    }
    vector<pair<int, int>> removers;
    for (int i = 0; i < N; i++) {
        if (status[i]) {
            removers.push_back({(status & keeps[i]).count(), i});
        }
    }
    sort(removers.begin(), removers.end());
    int limit = max(1, 50 - 5 * depth);
    if (removers.size() > limit) removers.resize(limit);
    known[status] = INF;
    for (auto [_, i]: removers) {
        int sol = dfs(status & keeps[i], depth + 1);
        known[status] = min(known[status], sol + 1);
        if (sol == 0) break;
    }
    return known[status];
}

int main() {
    start = clock();
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> V[i];

    bitset<MAXN> start;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (V[i] % V[j] && V[j] % V[i]) {
                keeps[i].set(j);
            }
        }
        start.set(i);
    }

    dfs(start);
    cout << best;
}