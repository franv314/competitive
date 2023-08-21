#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> primes;
vector<int> used;

void inizializza(int P, int M) {
    used.resize(M + 1);
    primes.resize(M + 1);
    
    for (int i = 2; i <= M; i++) {
        if (primes[i].empty()) {
            for (int j = i; j <= M; j += i) {
                primes[j].push_back(i);
            }
        }
    }
}

int controlla(int checksum) {

    for (auto p: primes[checksum]) {
        if (used[p]) {
            return used[p];
        }
    }
    
    for (auto p: primes[checksum]) {
        if (!used[p]) {
            used[p] = checksum;
        }
    }
    
    return 0;
}