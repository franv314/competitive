#include <bits/stdc++.h>
using namespace std;

struct Arco {
    int dest;
    int peso;
};

struct HeapElem {
    int nodo;
    int dst;
};

struct Compare {
    bool operator() (HeapElem a, HeapElem b) {
        return a.dst > b.dst;
    }
};

int my_min(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (a > b) return b;
    return a;
}

vector<Arco> archi[300000];
priority_queue<HeapElem, vector<HeapElem>, Compare> to_be_visited;
set<int> visited;

void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<int> &D) {
    for (int i = 0; i < M; i++) archi[X[i]].push_back({Y[i], P[i]});
    to_be_visited.push({0, 0});

    for (int i = 0; i < N; i++) D[i] = -1;

    while (visited.size() < N && !to_be_visited.empty()) {
        HeapElem best = to_be_visited.top();
        to_be_visited.pop();
        if (visited.find(best.nodo) != visited.end()) continue;
        D[best.nodo] = best.dst;
        visited.insert(best.nodo);

        for (auto arco: archi[best.nodo]) {
            if (visited.find(arco.dest) != visited.end()) continue;
            to_be_visited.push({arco.dest, my_min(D[arco.dest], D[best.nodo] + arco.peso)});
        }
    }
}