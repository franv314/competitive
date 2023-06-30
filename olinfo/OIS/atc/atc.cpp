/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <bits/stdc++.h>
using namespace std;

// constraints
#define MAXN 200

// input data
int N, i, x, y;
char grid[MAXN][MAXN + 1];


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

void dijkstra(int N, vector<Arco> archi[], vector<int> &D) {
    priority_queue<HeapElem, vector<HeapElem>, Compare> to_be_visited = {};
    set<int> visited = {};


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

int dijkstra(int N, vector<Arco> archi[], int pos) {
    priority_queue<HeapElem, vector<HeapElem>, Compare> to_be_visited = {};
    set<int> visited = {};

    to_be_visited.push({0, 0});

    vector<int> D;
    D.resize(N);
    for (int i = 0; i < N; i++) D[i] = -1;

    while (visited.size() < N && !to_be_visited.empty()) {
        HeapElem best = to_be_visited.top();
        to_be_visited.pop();
        if (best.nodo == pos) return best.dst;
        if (visited.find(best.nodo) != visited.end()) continue;
        D[best.nodo] = best.dst;
        visited.insert(best.nodo);

        for (auto arco: archi[best.nodo]) {
            if (visited.find(arco.dest) != visited.end()) continue;
            to_be_visited.push({arco.dest, my_min(D[arco.dest], D[best.nodo] + arco.peso)});
        }
    }
    return -1;
}

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &N));
    for(i=0; i<N; i++)
        assert(1 == scanf("%s", grid[i]));

    vector<Arco> archs[N*N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            archs[i * N + j].clear();
            x = i , y = j;
            while (++x < N && grid[x][y] == '.') {
                archs[i * N + j].push_back({x * N + y, 1});
            }
            if (x < N && grid[x][y] == 'T') {
                archs[i * N + j].push_back({x * N + y, 0});
            }

            x = i, y = j;
            while (--x >= 0 && grid[x][y] == '.') {
                archs[i * N + j].push_back({x * N + y, 1});
            }
            if (x >= 0 && grid[x][y] == 'T') {
                archs[i * N + j].push_back({x * N + y, 0});
            }

            x = i, y = j;
            while (++y < N && grid[x][y] == '.') {
                archs[i * N + j].push_back({x * N + y, 1});
            }
            if (y < N && grid[x][y] == 'T') {
                archs[i * N + j].push_back({x * N + y, 0});
            }

            x = i, y = j;
            while (--y >= 0 && grid[x][y] == '.') {
                archs[i * N + j].push_back({x * N + y, 1});
            }
            if (y >= 0 && grid[x][y] == 'T') {
                archs[i * N + j].push_back({x * N + y, 0});
            }
        }
    }
    int a = dijkstra(N * N, archs, N*N-1);

    printf("%d\n", a); // change 42 with actual answer
    return 0;
}