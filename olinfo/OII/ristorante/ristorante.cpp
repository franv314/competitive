#include <bits/stdc++.h>
using namespace std;

int cnt(int N, vector<int> &A, vector<int> &B, vector<int> &C) {
    unordered_set<int> taken;
    int ans = 0;
    int x = 0, y = 0, z = 0;
    for (; x < N; x++) {
        if (!taken.count(A[x])) {
            taken.insert(A[x]);
        } else break;
    }
    
    for (; x >= 0; x--) {
        for (; y < N; y++) {
            if (!taken.count(B[y])) {
                taken.insert(B[y]);
            } else break;
        }
        for (; z < N; z++) {
            if (!taken.count(C[z])) {
                taken.insert(C[z]);
            } else break;
        }
        ans = max(ans, (int)taken.size());
        if (x) taken.erase(A[x - 1]);
    }
    return ans;
}

int conta(int N, vector<int> &A, vector<int> &B, vector<int> &C) {
    return max({
        cnt(N, A, B, C),
        cnt(N, A, C, B),
        cnt(N, B, A, C),
        cnt(N, B, C, A),
        cnt(N, C, A, B),
        cnt(N, C, B, A),
    });
}
