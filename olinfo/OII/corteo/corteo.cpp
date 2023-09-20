#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000

void sposta(int chi, int dove);

struct DSU {
    vector<int> arr;
    
    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }
    
    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (arr[u] > arr[v]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;
    }
    
    DSU(int size) : arr(size, -1) {}  
};

int dst[MAXN][MAXN];
int queues[MAXN][MAXN];
int idx[MAXN];
int q[10 * MAXN * MAXN];
int l, r;
int adj[MAXN][MAXN];
int adj_idx[MAXN];

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {
    for (int i = 0; i < M; i++) {
        adj[A[i]][adj_idx[A[i]]++] = B[i];
        adj[B[i]][adj_idx[B[i]]++] = A[i];
    }
    
    for (int i = 0; i < N; i++) {
        int *qref = queues[i];
        int *dref = dst[i];
        q[r++] = i;
        dref[i] = 1;
        while (l != r) {
            int x = q[l++];
            
            qref[idx[i]++] = x;
            
            for (int j = 0; j < adj_idx[x]; j++) {
                int y = adj[x][j];
                if (!dref[y]) {
                    q[r++] = y;
                    dref[y] = dref[x] + 1;
                }
            }
        }
    }

    if (P1 == D1 && P2 == D2) {
        return dst[D1][D2] - 1;
    }
    
    DSU dsu(N * N);
    for (int dist = dst[D1][D2]; ; dist--) {
        for (int x = 0; x < N; x++) {
            int *qref = queues[x];
            while (dst[x][qref[idx[x] - 1]] >= dist) {
                int y = qref[--idx[x]];
                
                for (int j = 0; j < adj_idx[x]; j++) {
                    int x2 = adj[x][j];
                    if (dst[x2][y] >= dist) {
                        dsu.join(N * x + y, N * x2 + y);
                    }
                }
                for (int j = 0; j < adj_idx[y]; j++) {
                    int y2 = adj[y][j];
                    if (dst[x][y2] >= dist) {
                        dsu.join(N * x + y, N * x + y2);
                    }
                }
            }
        }
        
        if (dsu.find(P1 * N + P2) == dsu.find(D1 * N + D2)) {
            return dist - 1;
        }
    }
}