#include <bits/stdc++.h>
using namespace std;

void Colora(int N, int Q, vector <int> &A, vector <int> &B, vector <int> &C, vector <int> &murale){
    N++;
    vector<int> P(N,-1);

    while (Q--) {
        int l=A[Q],r=B[Q],c=C[Q];
        int pos=l;
        for (int i=l;i<=r;i++) {
            if (P[i]==-1) {
                murale[i]=c;
                P[i]=r;
            } else {
                i=P[i];
            }
        }
    }

    return;
}