#include <bits/stdc++.h>
using namespace std;

int Trova(int N, int K, int* insieme) {
    if (K == 1) return 0;
    
    set<int> S = {};
    set<int> D = {};
    for (int i = 0; i < N; i++) S.insert(insieme[i]);
    
    while (!S.empty()) {
        for (int lower = *S.begin(), i = 1; S.find(lower) != S.end(); lower *= K, i++) {
            S.erase(lower);
            if (i & 1) D.insert(lower);
        }
    }
    return D.size();
}