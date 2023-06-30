#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

struct Nodo {
    int l, f;
};

#define _ << " " <<
#define MAXN 100000

vector<Nodo> coincidenze[MAXN];

int pianifica(int N, int L, vector<vector<int>> F) {
    vector<vector<int>> dst = {};
    vector<vector<bool>> visited = {};
    deque<Nodo> q = {};

    for (int l = 0; l < F.size(); l++) {
        dst.push_back(vector<int>(F[l].size(), 2e9));
        visited.push_back(vector<bool>(F[l].size(), false));

        for (int f = 0; f < F[l].size(); f++) {
            if (F[l][f] == 0) {
                dst[l][f] = 0;
                q.push_back({l, f});
            }
            coincidenze[F[l][f]].push_back({l, f});
        }
    }

    while (!q.empty()) {
        auto top = q.front();
        q.pop_front();
        int top_dst = dst[top.l][top.f];

        if (visited[top.l][top.f]) continue;
        if (F[top.l][top.f] == N - 1) return top_dst;

        visited[top.l][top.f] = true;
        
        if (top.f < F[top.l].size() - 1 && dst[top.l][top.f + 1] > top_dst) {
            dst[top.l][top.f + 1] = top_dst;
            q.push_front({top.l, top.f + 1});
        }
        for (auto x: coincidenze[F[top.l][top.f]]) {
            if (dst[x.l][x.f] > top_dst + 1) {
                dst[x.l][x.f] = top_dst + 1;
                q.push_back(x);
            }
        }
        coincidenze[F[top.l][top.f]].clear();
    }
    return -1;
}