#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001
#define _ << " " <<

optional<int> last_r[MAXN], last_c[MAXN];
vector<pair<int, int>> E;
bitset<MAXN> known_rows, known_cols, visited;
vector<int> neighbours[MAXN];

int useless;

void dfs(int node) {
    visited[node] = true;

    auto [x, y] = E[node];

    if (known_rows[x] && known_cols[y]) useless++;

    known_rows[x] = true;
    known_cols[y] = true;

    for (auto neighbour: neighbours[node]) {
        if (!visited[neighbour]) {
            dfs(neighbour);
        }
    }
}

long long compra(int N, int M, int K, vector<pair<int, int>> E) {
    ::E = E;

    for (int i = 0; i < K; i++) {
        auto [x, y] = E[i];
        if (last_r[x]) {
            neighbours[i].push_back(last_r[x].value());
            neighbours[last_r[x].value()].push_back(i);
        }
        if (last_c[y]) {
            neighbours[i].push_back(last_c[y].value());
            neighbours[last_c[y].value()].push_back(i);
        }

        last_r[x] = last_c[y] = i;
    }

    for (int i = 0; i < K; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    return N + M - 1 - K + useless;
}