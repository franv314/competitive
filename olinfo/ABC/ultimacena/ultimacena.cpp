#include <bits/stdc++.h>
using namespace std;

int copertura(set<int> cover, int M, int A[], int B[], int S[]) {
    vector<set<int>> foglie = {};
    foglie.push_back(cover);
    
    for (int m = 0; m < M; m++) {
        int f = foglie.size();
        for (int i = 0; i < f; i++) {
            set<int> &foglia = foglie[i];
            if (
                foglia.size() < 10
                && foglia.find(A[m]) == foglia.end()
                && foglia.find(B[m]) == foglia.end()
            ) {
                set<int> new_foglia = foglia;
                foglia.insert(A[m]);
                new_foglia.insert(B[m]);

                foglie.push_back(new_foglia);
            }
        }
    }

    for (auto cov: foglie) {
        vector<bool> is_covered(M, false);
        for (int m = 0; m < M; m++) {
            is_covered[m] = cov.find(A[m]) != cov.end() || cov.find(B[m]) != cov.end(); 
        }
        
        if (accumulate(is_covered.begin(), is_covered.end(), true, logical_and<bool>())) {
            int k = 0;
            for (auto x: cov) S[k++] = x;
            return k;
        }
    }
}

int riassumi(int N, int M, int A[], int B[], int S[]) {
    vector<int> deg(N, 0);
    for (int m = 0; m < M; m++) {
        deg[A[m]]++;
        deg[B[m]]++;
    }

    set<int> cover = {};
    int i = 0;
    for (int n = 0; n < N; n++) {
        if (deg[n] > 10) {
            cover.insert(n);
        }
    }

    return copertura(cover, M, A, B, S);
}