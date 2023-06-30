#include <bits/stdc++.h>
using namespace std;

#define MAXX 500000

int arrivals[MAXX];

vector<int> cucina(int N, int K, int X, vector<int> H) {
    for (auto h: H)
        arrivals[h]++;
    
    vector<int> can_serve_after(X + 1, 0);
    int queue_space = K;
    for (int x = X - 1; x >= 0; x--) {
        int can_serve = min(queue_space, arrivals[x]);
        queue_space = min(K, queue_space + 1 - can_serve);

        can_serve_after[x] = min(can_serve_after[x + 1] + can_serve, X - x);
    }
    can_serve_after.pop_back();
    return can_serve_after;
}