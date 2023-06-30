#include <bits/stdc++.h>
using namespace std;

const int source = INT_MAX;
const int sink = INT_MIN;

void imp() {
    cout << "No\n";
    exit(0);
}

map<int, map<int, int>> adj;
map<int, int> rows, cols;
set<int> visited;
multiset<int> values;

int dfs(int node) {
    if (node == sink)
        return *values.begin();

    visited.insert(node);
    for (auto [neighbour, flow]: adj[node]) {
        if (flow && visited.find(neighbour) == visited.end()) {
            values.insert(flow);
            int f = dfs(neighbour);

            if (f) {
                adj[node][neighbour] -= f;
                adj[neighbour][node] += f;
                return f;
            }

            values.erase(flow);
        }
    }
    return 0;
}

int main() {
    int N;
    cin >> N;

    for (int _ = 0; _ < N; _++) {
        int X, Y; cin >> X >> Y;
        X++, Y++;

        rows[X]++, cols[Y]++;
        adj[X][-Y] = 1;
        adj[-Y][X] = 0;
    }

    for (auto [X, am]: rows) {
        if (am % 3) imp();
        adj[source][X] = am / 3;
        adj[X][source] = 0;
    }
    for (auto [Y, am]: cols) {
        if (am % 3) imp();
        adj[sink][-Y] = 0;
        adj[-Y][sink] = am / 3;
    }

    cout << "Yes\n" << N / 3 << endl;
    while (dfs(source)) {
        visited.clear();
        values.clear();
    }

    for (auto [X, x]: rows)
        for (auto [Y, f]: adj[X])
            if (!f)
                cout << X - 1 << " " << - Y - 1 << endl;
}