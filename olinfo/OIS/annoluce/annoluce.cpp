#include <bits/stdc++.h>
using namespace std;

int N;
vector<long long> stars;

void mappatura(int N, int X[], int Y[], int Z[]) {
    ::N = N;
    stars.resize(N);
    for (int i = 0; i < N; i++)
        stars[i] = X[i] * (long long)X[i] + Y[i] * (long long)Y[i] + Z[i] * (long long)Z[i];
    sort(stars.begin(), stars.end());
}

int query(int D) {
    int l = 0, r = N;
    while (l < r) {
        int m = (l + r) / 2;
        if (stars[m] > D * (long long)D)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

#define MAXN 100000
int X[MAXN], Y[MAXN], Z[MAXN];

int main() {
    FILE *fr, *fw;
    int N, Q, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
    for(i=0; i<N; i++)
        assert(3 == fscanf(fr, "%d%d%d", &X[i], &Y[i], &Z[i]));

    mappatura(N, X, Y, Z);

    assert(1 == fscanf(fr, "%d", &Q));
    for(i=0; i<Q; i++) {
        int D;
        assert(1 == fscanf(fr, "%d", &D));
        fprintf(fw, "%d\n", query(D));
    }

    fclose(fr);
    fclose(fw);
    return 0;
}