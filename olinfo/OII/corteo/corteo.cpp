#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1000];
vector<vector<int>> dst;
int P1, P2, D1, D2;

void sposta(int chi, int dove);

bool test(int threshold) {
    bool visited[1000][1000] = {};
    queue<pair<int, int>> q;

    if (dst[P1][P2] >= threshold) q.push({P1, P2});
    while (!q.empty()) {
        auto [p1, p2] = q.front();
        q.pop();
        if (visited[p1][p2]) continue;
        if (p1 == D1 && p2 == D2) return true;

        visited[p1][p2] = true;
        for (auto d1: adj[p1])
            if (!visited[d1][p2] && dst[d1][p2] >= threshold)
                q.push({d1, p2});
        for (auto d2: adj[p2])
            if (!visited[p1][d2] && dst[p1][d2] >= threshold)
                q.push({p1, d2});
    }
    return false;
}

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {
    ::P1 = P1, ::P2 = P2, ::D1 = D1, ::D2 = D2;
    dst = vector<vector<int>>(N, vector<int>(N, 1e9));

    // Populate adjacency list
    for (int i = 0; i < M; i++) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    // Populate distances
    for (int i = 0; i < N; i++) {
        queue<pair<int, int>> q;
        
        q.push({i, 0});
        while (!q.empty()) {
            auto [node, d] = q.front();
            q.pop();
            if (dst[i][node] != 1e9) continue;
            
            dst[i][node] = d;
            for (auto dest: adj[node])
                if (dst[i][dest] == 1e9)
                    q.push({dest, d + 1});
        }
    }

    int l = 0, r = min(dst[P1][P2], dst[D1][D2]) + 1;
    while (l + 1 < r) test((l + r) / 2) ? l = (l + r) / 2 : r = (l + r) / 2;
    return l;
}
