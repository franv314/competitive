#include <bits/stdc++.h>
using namespace std;

int N, M;
int u, v;
long long w;
vector<tuple<long long, int, int>> edges;

ifstream in("input.txt");
ofstream out("output.txt");

class DSU {
    vector<int> nodes;

public:

    int find(int elem) {
        while (nodes[elem] >= 0) elem = nodes[elem];
        return elem;
    }

    void join(int i, int j) {
        int s_i = find(i), s_j = find(j);
        if (s_i == s_j) return;
        if (nodes[s_i] < nodes[s_j]) {
            nodes[s_i] += nodes[s_j];
            nodes[s_j] = s_i;
        } else {
            nodes[s_j] += nodes[s_i];
            nodes[s_i] = s_j;
        }
    }

    DSU(int N) {
        nodes = vector<int>(N + 1, -1);
    }

};

void read_input() {
    ios::sync_with_stdio(false);
    in.tie(NULL);

    in >> N >> M;
    edges.resize(M);
    for (int m = 0; m < M; m++) {
        in >> u >> v >> w;
        edges[m] = {w, u, v};
    }
}

void solve() {
    sort(edges.begin(), edges.end());
    DSU dsu(N);

    vector<pair<int, int>> mst;
    long long weight = 0;

    for (auto [W, U, V]: edges) {
        if (dsu.find(U) != dsu.find(V)) {
            mst.push_back({U, V});
            weight += W;
            dsu.join(U, V);
        }
    }

    out << weight << endl;
    for (auto [U, V]: mst)
        out << U << " " << V << endl;
}

int main() {
    read_input();
    solve();
    return 0;
}