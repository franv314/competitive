#include <bits/stdc++.h>
using namespace std;

#define MAXN 2000

int N;
bool adj[MAXN][MAXN];

vector<int> nodes;
set<int> visited;

void dfs(int node) {
    nodes.push_back(node);
    visited.insert(node);
    for (int i = 0; i < N; i++) {
        if (adj[node][i]) {
            if (nodes[nodes.size() - 3] == i) {
                cout << 1 + nodes[nodes.size() - 1] << " "
                     << 1 + nodes[nodes.size() - 2] << " "
                     << 1 + nodes[nodes.size() - 3] << endl;
                exit(0);
            }
            else if (visited.find(i) == visited.end()) dfs(i);
        }
    }
    nodes.pop_back();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> adj[j][i];
    dfs(0);
    cout << "-1\n";
}