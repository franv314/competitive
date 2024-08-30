
#include <bits/stdc++.h>
#include "pizza.h"
using namespace std;

#define MAXI 8

queue<int> orders[1 << MAXI];
int amounts[MAXI];
int cnt;

void Init() {
}

void Order(int N, int *A) {
    int me = cnt++;

    int order = 0;
    bool ok = true;
    for (int i = 0; i < N; i++) {
        order |= 1 << A[i];
        ok &= (bool)amounts[A[i]];
    }

    if (!ok) {
        orders[order].push(me);
    } else {
        Bake(me);
        for (int i = 0; i < N; i++)
            amounts[A[i]]--;
    }
}

void Delivery(int I) {
    amounts[I]++;
    pair<int, int> earliest = {1e9, 1e9};

    for (int i = 0; i < (1 << MAXI); i++) {
        if (orders[i].empty()) continue;
        
        bool ok = true;
        for (int j = 0; j < MAXI; j++)
            if ((i >> j) & 1)
                ok &= (bool)amounts[j];
        
        if (ok)
            earliest = min(earliest, {orders[i].front(), i});
    }

    if (earliest.first == 1e9) return;

    Bake(earliest.first);
    orders[earliest.second].pop();
    for (int i = 0; i < MAXI; i++)
        if ((earliest.second >> i) & 1)
            amounts[i]--;
}
