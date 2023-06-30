#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

#define MAXN 10000
vector<int> adj[MAXN];
bool visited[MAXN][420];
bool occupied[MAXN][420];

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    for (int i = 0; i < K; i++){
        int L;
        cin >> L; 
        vector<int> H(L);
        for (int j = 0; j < L; j++) cin >> H[j];
        for (int k = 0; k < 420; k++) occupied[H[k % L]][k] = true;
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [node, time] = q.front();
        q.pop();
        if (visited[node][time % 420]) continue;
        if (node == N - 1) {
            cout << time << endl;
            return 0;
        }

        visited[node][time % 420] = true;
        for (auto x: adj[node]) {
            if (occupied[x][(time + 1) % 420]) continue;
            q.push({x, time + 1});
        }
        if (!occupied[node][(time + 1) % 420]) {
            q.push({node, time + 1});
        }
    }

    cout << -1 << endl; // print the result
    
    return 0;
}