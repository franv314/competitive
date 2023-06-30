#include <bits/stdc++.h>
using namespace std;

struct Nodo {
    int n, k;
    long long d;
};

struct Compare {
    bool operator()(Nodo a, Nodo b) {
        return a.d > b.d;
    }
};

#define MAXN 1000
#define MAXK 75

typedef tuple<int, int, int, int> arco_t;
vector<arco_t> adj[MAXN];

long long dst[MAXN][MAXK + 1];
bool visited[MAXN][MAXK + 1];

int N, K, S, E;

long long fastest(int max_volontarie) {
    for (int n = 0; n < N; n++) {
        for (int k = 0; k <= K; k++) {
            visited[n][k] = false;
            dst[n][k] = 1e18;
        }
    }
    
    priority_queue<Nodo, vector<Nodo>, Compare> q = {};
    for (int k = 0; k <= K; k++) {
        dst[S][k] = 0;
        q.push({S, k, 0});
    }

    while (!q.empty()) {
        Nodo top = q.top();
        q.pop();
        if (visited[top.n][top.k]) continue;
        if (top.n == E && top.k == K) return top.d;

        visited[top.n][top.k] = true;

        for (auto arco: adj[top.n]) {
            auto [d, w, p, v] = arco;
            if (top.k < K && top.d + p < dst[d][top.k + 1]) {
                dst[d][top.k + 1] = top.d + p;
                q.push({d, top.k + 1, top.d + p});
            }
            if (max_volontarie >= v && top.d + w < dst[d][top.k]) {
                dst[d][top.k] = top.d + w;
                q.push({d, top.k, top.d + w});
            }
        }
    }
    return INT64_MAX;
}

int avoid_volunteers(int subtask, int N, int M, int K, int S, int E, int T,
                     int A[], int B[], int W[], int P[], int V[]) {
    // Popolo la lista di adiacenza e le variabili globali
    for (int m = 0; m < M; m++) {
        adj[A[m]].push_back({B[m], W[m], P[m], V[m]});
        adj[B[m]].push_back({A[m], W[m], P[m], V[m]});
    }
    ::N = N, ::K = K, ::S = S, ::E = E;

    // Ordino le volontarie
    sort(V, V + M);

    // Se non posso evitare neanche la strada con più volontarie
    // allora non c'è nessuna strada valida
    if (fastest(V[M - 1]) > T)
        return -1;

    // Altrimenti bin-search
    int l = 0, r = M - 2;
    while (l < r) {
        int m = (l + r) / 2;
        if (fastest(V[m]) <= T)
            r = m;
        else
            l = m + 1;
    }
    return V[l];
}