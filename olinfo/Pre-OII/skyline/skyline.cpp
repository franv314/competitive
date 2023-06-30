#include <bits/stdc++.h>
using namespace std;

int M, *H;
long long sum;
multiset<int, greater<int>> heights;

void Inizializza(int N, int M, int* H) {
    ::M = M, ::H = H;
    sum = accumulate(H, H + N, 0ll);
    for (int i = 0; i < N; i++) {
        heights.insert(H[i]);
    }
}

int Cambia(int P, int V) {
    sum += V - H[P];
    heights.erase(heights.find(H[P]));
    heights.insert(V);
    H[P] = V;

    return sum % M == 0 && *heights.begin() <= sum / M;
}